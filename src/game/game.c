#include "game.h"
#include <stdio.h>

#define QUAD_DATA_LENGTH 6 * 6

Game game;

void game_init(void)
{
    game.rotation = 0.8;
    game.buffer_length = 0;
    game.buffer = malloc(10000 * sizeof(f32));
    game.objects = dll_create();
    game_insert(data_create(drawable_create(vec3f_create(0, 0, 0), vec3f_create(0.2, 0.9, 0.2), entity_create(PLAYER), ENTITY), QUAD_DATA_LENGTH, game.buffer_length));
    game_insert(data_create(drawable_create(vec3f_create(1, 3, 0), vec3f_create(0.5, 0.5, 0.5), tile_create(WALL), TILE), 5 * QUAD_DATA_LENGTH, game.buffer_length));
    game_insert(data_create(drawable_create(vec3f_create(1, 0, 1), vec3f_create(0.3, 0.5, 0.7), tile_create(FLOOR), TILE), QUAD_DATA_LENGTH, game.buffer_length));
    // game_remove(game.objects.head->data);
}

void game_clear(void)
{
    while (!dll_empty(&game.objects))
        game_remove(game.objects.head->data);
}

void game_remove(Data* data)
{
    game.buffer_length -= data->length;
    game.objects.tail->data->offset = data->offset;
    dll_replace(&game.objects, data->node);
    drawable_destroy(data->val);
    data_destroy(data);
}

void game_insert(Data* data)
{
    game.buffer_length += data->length;
    drawable_vertex_data(game.buffer, data->val, data->offset, game.rotation);
    dll_append(&game.objects, dll_node_create(data));
}

void game_set_target(vec3f target)
{
    f32 x = target.x;
    x = x + 1;
}

void game_set_rotation(f32 rotation)
{
    game.rotation = rotation;
    drawable_vertex_data(game.buffer, game.objects.head->data->val, game.objects.head->data->offset, game.rotation);
}

void game_destroy(void)
{
    free(game.buffer);
}