#include "game.h"
#include <stdio.h>
#include <assert.h>

#define MAX_BUFFER_LENGTH 100000

Game game;
Data* player;

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
}

void game_setup(void)
{
    game_insert(data_create(drawable_create(vec3f_create(1, 0, 1), vec3f_create(0.8, 0.5, 0.7), tile_create(FLOOR), TILE), QUAD_DATA_LENGTH, game.buffer_length));
    game_insert(data_create(drawable_create(vec3f_create(1, 3, 0), vec3f_create(0.5, 0.5, 0.5), tile_create(WALL), TILE), 5 * QUAD_DATA_LENGTH, game.buffer_length));
    player = data_create(drawable_create(vec3f_create(0, 0, 0), vec3f_create(0.5, 0.5, 0.8), entity_create(PLAYER), ENTITY), QUAD_DATA_LENGTH, game.buffer_length);
    game_insert(player);
}

void game_update(void)
{
    DLLNode* n = game.entities.head;
    while (n != NULL)
        drawable_vertex_data(game.buffer, n->data->val, n->data->offset, game.rotation, game.tilt), n = n->next;
}

void game_clear(void)
{
    while (!dll_empty(&game.objects))
        game_remove(game.objects.head->data);
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

void game_insert(Data* data)
{
    game.buffer_length += data->length;
    assert(game.buffer_length < MAX_BUFFER_LENGTH);
    drawable_vertex_data(game.buffer, data->val, data->offset, game.rotation, game.tilt);
    if (((Drawable*)data->val)->type == TILE)
        dll_append(&game.tiles, dll_node_create(data));
    else
        dll_append(&game.entities, dll_node_create(data));
}

void game_set_target(vec3f target)
{
    ((Drawable*)player->val)->position = target;
    drawable_vertex_data(game.buffer, player->val, player->offset, game.rotation, game.tilt);
}

void game_set_rotation(f32 rotation)
{
    game.rotation = rotation;
}

void game_set_tilt(f32 tilt)
{
    game.tilt = tilt;
}

void game_destroy(void)
{
    free(game.buffer);
}

void game_shoot(void)
{
    vec3f pos = ((Drawable*)player->val)->position;
    pos.y = 0.5;
    game_insert(data_create(drawable_create(pos, vec3f_create(0.9, 0.2, 0), entity_create(PROJECTILE), ENTITY), QUAD_DATA_LENGTH, game.buffer_length));
}