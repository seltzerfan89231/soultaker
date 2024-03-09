#include "game.h"

Game game;

void game_init(void)
{
    game.buffer = malloc(20000 * sizeof(f32));
    game.buffer_size = 0;
    game.objects = dll_create();
    for (i32 i = 0; i < MAP_WIDTH * MAP_WIDTH; i++) {
        if (i % 7 == 0) 
            game_insert(data_create(tile_create(i / MAP_WIDTH, 3, i % MAP_WIDTH, 0.5f, 0.5f, 0.5f, WALL)));
        else
            game_insert(data_create(tile_create(i / MAP_WIDTH, 0, i % MAP_WIDTH, 0.7f, 0.3f, 0.2f, FLOOR)));
    }
}

void game_clear(void)
{
    while (!dll_empty(&game.objects))
        game_remove(game.objects.head->data);
}

void game_remove(Data* data)
{
    dll_remove(&game.objects, data->node);
    data_destroy(data);
}

void game_insert(Data* data)
{
    dll_push(&game.objects, dll_node_create(data));
}

void game_destroy(void)
{
    free(game.buffer);
}