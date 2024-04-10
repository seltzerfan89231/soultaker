#include "game.h"
#include "../util/buffertype.h"
#include <stdio.h>
#include <assert.h>
#include <glfw.h>

Game game;
Entity* player;

static void push_data(Data* data);
static void remove_data(Data* data);

void game_init(void)
{
    game.tile_buffer = game.entity_buffer = game.gui_buffer = NULL;
    game.tile_length = game.entity_length = game.gui_length = 0;
    game.tiles = dll_create();
    game.entities = dll_create();
    game.rotation = game.tilt = 0;
}

void game_setup(void)
{
    game.tile_buffer = malloc(MAX_BUFFER_LENGTH * sizeof(f32));
    for (f32 i = 0; i < 30; i++) {
        for (f32 j = 0; j < 30; j++) {
            Tile* tile;
            if (i == 0 || i == 29 || j == 0 || j == 29)
                tile = tile_create(WALL);
            else
                tile = tile_create(FLOOR);
            tile->position = vec2f_create(i, j);
            push_data(data_create(tile, game.tile_length, TILE));
        }
    }
    remove_data(game.tiles.head->next->next->next->next->data);
    game.tile_buffer = realloc(game.tile_buffer, game.tile_length * sizeof(f32));
    
    game.gui_buffer = malloc(MAX_BUFFER_LENGTH * sizeof(f32));
    gui_push_data(game.gui_buffer, &game.gui_length);
    game.gui_buffer = realloc(game.gui_buffer, game.gui_length * sizeof(f32));

    game.entity_buffer = malloc(MAX_BUFFER_LENGTH * sizeof(f32));
    player = entity_create(PLAYER);
    player->position = vec3f_create(0.0f, 0.0f, 0.0f);
    push_data(data_create(player, game.entity_length, ENTITY));
}

void game_update(f32 dt)
{
    DLLNode* n = game.entities.head;
    while (n != NULL) {
        entity_update_data((Entity*)n->data->val, game.entity_buffer, n->data->offset);
        n = n->next;
    }
}

void game_set_target(vec3f target)
{
    player->position = target;
}

void game_set_rotation(f32 rotation)
{
    game.rotation = rotation;
    entity_update_rotation(rotation);
}

void game_set_tilt(f32 tilt)
{
    game.tilt = tilt;
    entity_update_tilt(tilt);
}

void game_destroy(void)
{
    free(game.tile_buffer);
    free(game.entity_buffer);
    free(game.gui_buffer);
}

void game_shoot(vec2f dir)
{
    /* static f32 cooldown;
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
    dir.x =  dir.x > 0 ? 1 / sqrt(c) : -1 / sqrt(c);
    dir.y = -dir.y > 0 ? sqrt(1 - 1 / c) : -sqrt(1 - 1 / c);
    dirx = dir.x * cos(game.rotation - HALFPI) - dir.y * sin(game.rotation - HALFPI);
    dirz = dir.x * sin(game.rotation - HALFPI) + dir.y * cos(game.rotation - HALFPI);
    proj->direction = vec3f_normalize(vec3f_create(dirx, 0, dirz));
    vec3f start = player->position;
    start.y = 0.0;
    game_insert(drawable_create(start, vec2f_create(0.5, 0), proj, ENTITY)); */
}

void push_data(Data* data)
{
    DLLNode* node = dll_node_create(data);
    switch (data->type) {
        case TILE:
            dll_push(&game.tiles, node);
            tile_push_data((Tile*)data->val, game.tile_buffer, &game.tile_length);
            break;
        case ENTITY:
            dll_push(&game.entities, node);
            entity_push_data((Entity*)data->val, game.entity_buffer, &game.entity_length);
            break;
        case GUI:
            break;
    }
}

void remove_data(Data* data)
{
    switch (data->type) {
        case TILE:
            tile_remove_data((Tile*)data->val, game.tile_buffer, data->offset);
            break;
        case GUI:
            break;
    }
    dll_node_destroy(data->node);
    data_destroy(data);
}