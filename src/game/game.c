#include "game.h"
#include <stdio.h>
#include <assert.h>
#include <glfw.h>

Game game;
Drawable* player;

static void buffer_remove_tile(Tile* tile, u32 offset)
{
    i32 length = QUAD_DATA_LENGTH * (tile->type == FLOOR ? NUM_FLOOR_SIDES : NUM_WALL_SIDES);
    for (u32 i = offset; i < offset + length; i++)
        game.buffer[i] = 0;
}

void game_init(void)
{
    game.buffer_length = 0;
    game.buffer = malloc(MAX_BUFFER_LENGTH * sizeof(f32));
    game.tiles = dll_create();
    game.entities = dll_create();
    player = NULL;
}

void game_setup(void)
{
    for (i32 i = 0; i < MAP_WIDTH; i++)
        for (i32 j = 0; j < MAP_WIDTH; j++) {
            if (i == 0 || i == MAP_WIDTH - 1 || j == 0 || j == MAP_WIDTH - 1)
                game_insert(drawable_create(vec3f_create(i, 3, j), vec2f_create(0.25, 0), tile_create(WALL), TILE));
            else
                game_insert(drawable_create(vec3f_create(i, 0, j), vec2f_create(0.25, 0), tile_create(FLOOR), TILE));
    }
    player = drawable_create(vec3f_create(0, 0, 0), vec2f_create(0, 0), entity_create(PLAYER, 1), ENTITY);
    game_insert(player);
}

void game_update(f32 dt)
{
    if (dll_empty(&game.entities))
        return;
    DLLNode* n = game.entities.head;
    while (n != NULL) {
        drawable_update(n->data->val, dt);
        drawable_vertex_data(game.buffer, n->data->val, n->data->offset);
        n = n->next;
    }
}

void game_clear(void)
{
    while (!dll_empty(&game.tiles))
        game_remove(game.tiles.head->data);
    while (!dll_empty(&game.entities))
        game_remove(game.entities.head->data);
    game.buffer_length = 0;
    player = NULL;
}

void game_remove(Data* data)
{
    if (((Drawable*)data->val)->type == TILE) {
        buffer_remove_tile((Tile*)((Drawable*)data->val)->obj, data->offset);
        dll_remove(&game.tiles, data->node);
    }
    else {
        game.buffer_length -= data->length;
        game.entities.tail->data->offset = data->offset;
        dll_replace(&game.entities, data->node);
    }
    drawable_destroy(data->val);
    data_destroy(data);
}

void game_insert(Drawable* drawable)
{
    Data* data = data_create(drawable, (drawable->type == TILE && ((Tile*)drawable->obj)->type == WALL ? 5 : 1) * QUAD_DATA_LENGTH, game.buffer_length);
    game.buffer_length += data->length;
    assert(game.buffer_length < MAX_BUFFER_LENGTH);
    if (drawable->type == TILE)
        dll_append(&game.tiles, dll_node_create(data));
    else
        dll_append(&game.entities, dll_node_create(data));
    drawable_vertex_data(game.buffer, data->val, data->offset);
}

void game_set_target(vec3f target)
{
    assert(player != NULL);
    player->position = target;
}

void game_update_rotation(f32 rotation)
{
    drawable_update_rotation(game.rotation = rotation);
}

void game_update_tilt(f32 tilt)
{
    drawable_update_tilt(game.tilt = tilt);
}

void game_destroy(void)
{
    free(game.buffer);
}

void game_shoot(vec2f dir)
{
    static f32 cooldown;
    if (glfwGetTime() - cooldown < 0.05)
        return;
    cooldown = glfwGetTime();
    assert(player != NULL);
    Entity* proj = entity_create(PROJECTILE, 0.5);
    proj->speed = 4;
    f32 dirx, dirz, a, b, c;
    a = atan(-dir.y/dir.x);
    b = PI/2 + game.tilt;
    c = tan(a) * tan(a) / cos(b) / cos(b) + 1;
    // dirx = dir.x * cos(game.rotation - HALFPI) - -dir.y * sin(game.rotation - HALFPI);
    // dirz = dir.x * sin(game.rotation - HALFPI) + -dir.y * cos(game.rotation - HALFPI);
    dirx = 1 / sqrt(c);
    dirz = sqrt(1 - 1 / c);
    printf("%f, %f, %f, %f\n", a, b, dirx, dirz);
    proj->direction = vec3f_normalize(vec3f_create(dirx, 0, dirz));
    vec3f start = player->position;
    start.y = 0.0;
    game_insert(drawable_create(start, vec2f_create(0.5, 0), proj, ENTITY));
}