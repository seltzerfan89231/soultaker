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
    for (f32 i = 15; i < 30; i++) {
        for (f32 j = 15; j < 30; j++) {
            Tile* tile;
            if (i == 0 || i == 29 || j == 0 || j == 29)
                tile = tile_create(WALL);
            else
                tile = tile_create(FLOOR);
            tile->position = vec2f_create(i, j);
            push_data(data_create(tile, game.tile_length, TILE));
        }
    }
    game.tile_buffer = realloc(game.tile_buffer, game.tile_length * sizeof(f32));
    
    game.gui_buffer = malloc(MAX_BUFFER_LENGTH * sizeof(f32));
    gui_push_data(game.gui_buffer, &game.gui_length);
    game.gui_buffer = realloc(game.gui_buffer, game.gui_length * sizeof(f32));

    game.entity_buffer = malloc(MAX_BUFFER_LENGTH * sizeof(f32));
    player = entity_create(PLAYER);
    player->position = vec3f_create(0.0f, 0.0f, 0.0f);
    Data* player_data = data_create(player, game.entity_length, ENTITY);
    push_data(player_data);

    for (i32 i = 0; i < 10; i++) {
        for (i32 j = 0; j < 10; j++) {
            Entity* entity = entity_create(PLAYER);
            entity->position = vec3f_create(3 * i + 2, 0, 3 * j + 2);
            Data* entity_data = data_create(entity, game.entity_length, ENTITY);
            push_data(entity_data);
        }
    }

    dll_clear(&game.tiles);
}

void game_update(f32 dt)
{
    DLLNode* n = game.entities.head;
    while (n != NULL) {
        Entity* entity = n->data->val;
        entity_update_position(entity, dt);
        entity_update_data(entity, game.entity_buffer, n->data->offset);
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
    dll_destroy(&game.tiles);
    dll_destroy(&game.entities);
}

void game_shoot(vec2f dir)
{
    static f32 cooldown;
    if (glfwGetTime() - cooldown < 0.05)
        return;
    cooldown = glfwGetTime();
    assert(player != NULL);
    Entity* proj = entity_create(PROJECTILE);
    proj->speed = 4;
    f32 dirx, dirz, a, b, c;
    a = atan(-dir.y/dir.x);
    b = PI/2 + game.tilt;
    c = tan(a) * tan(a) / cos(b) / cos(b) + 1;
    dir.x =  dir.x > 0 ? 1 / sqrt(c) : -1 / sqrt(c);
    dir.y = -dir.y > 0 ? sqrt(1 - 1 / c) : -sqrt(1 - 1 / c);
    dirx = dir.x * cos(game.rotation - HALFPI) - dir.y * sin(game.rotation - HALFPI);
    dirz = dir.x * sin(game.rotation - HALFPI) + dir.y * cos(game.rotation - HALFPI);
    proj->position = player->position;
    // proj->position.y = 0.5;
    proj->direction = vec3f_normalize(vec3f_create(dirx, 0, dirz));
    proj->tex = vec2f_create(0.5, 0);
    push_data(data_create(proj, game.entity_length, ENTITY));
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
    DLLNode* node = data->node;
    switch (data->type) {
        case TILE:
            dll_remove(&game.tiles, node);
            tile_remove_data((Tile*)data->val, game.tile_buffer, data->offset);
            break;
        case ENTITY:
            Data* new = game.entities.tail->data;
            dll_replace(&game.entities, node);
            if (new != NULL) {
                new->offset = data->offset;
                entity_update_data((Entity*)new->val, game.entity_buffer, new->offset);
            }
            game.entity_length -= 6 * 5;
            break;
        case GUI:
            break;
    }
    dll_node_destroy(data->node);
}