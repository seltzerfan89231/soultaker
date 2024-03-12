#include "game.h"
#include <stdio.h>

#define QUAD_DATA_LENGTH 6 * 6

Game game;

void game_init(void)
{
    game.buffer_length = 0;
    game.buffer = malloc(10000 * sizeof(f32));
    game.objects = dll_create();
    game_insert(data_create(tile_create(0, 3, 0, 0.5f, 0.5f, 0.5f, WALL), 5 * QUAD_DATA_LENGTH, game.buffer_length));
    game_insert(data_create(tile_create(1, 3, 0, 0.5f, 0.5f, 0.5f, WALL), 5 * QUAD_DATA_LENGTH, game.buffer_length));
    game_insert(data_create(tile_create(0, 3, 1, 0.5f, 0.5f, 0.5f, WALL), 5 * QUAD_DATA_LENGTH, game.buffer_length));
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
    tile_vertex_data(game.buffer, game.objects.tail->data->obj, game.objects.tail->data->offset);
    dll_replace(&game.objects, data->node);
    data_destroy(data);
}

void game_insert(Data* data)
{
    game.buffer_length += data->length;
    tile_vertex_data(game.buffer, data->obj, data->offset);
    dll_append(&game.objects, dll_node_create(data));
}

void game_destroy(void)
{
    free(game.buffer);
}