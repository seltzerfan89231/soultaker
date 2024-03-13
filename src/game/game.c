#include "game.h"
#include <stdio.h>

#define QUAD_DATA_LENGTH 6 * 6

Game game;

void game_init(void)
{
    game.buffer_length = 0;
    game.buffer = malloc(10000 * sizeof(f32));
    game.objects = dll_create();
    game_insert(data_create(drawable_create(vec3f_create(1, 3, 0), vec3f_create(0.5, 0.5, 0.5), tile_create(WALL), TILE), 5 * QUAD_DATA_LENGTH, game.buffer_length));
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
    drawable_vertex_data(game.buffer, data->val, data->offset);
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
}

void game_destroy(void)
{
    free(game.buffer);
}