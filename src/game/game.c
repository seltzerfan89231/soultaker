#include "game.h"

void game_init(void)
{
    tilemap_init();
}

VertexData game_vertex_data(void)
{
    VertexData vertex_data;
    void** tilemap_data = tilemap_vertex_data();
    vertex_data.data_size = *(size_t*)(tilemap_data[0]);
    vertex_data.data = (f32*)(tilemap_data[1]);
    free((size_t*)tilemap_data[0]);
    free(tilemap_data);
    return vertex_data;
}