#include "tilemap.h"
#include <gvec.h>
#include <stdlib.h>

#define NUM_WALL_SIDES 5
#define NUM_TILE_SIDES 1
#define VERTEX_COUNT 6
#define FIELD_COUNT 6

TileMap tilemap;

static f32 s_vertices[] = {
    0, 0, 0,
    1, 0, 0,
    1, 1, 0,
    0, 1, 0,
    0, 0, 1,
    1, 0, 1,
    1, 1, 1,
    0, 1, 1
};

static u32 side_idxs[] = {
    2, 1, 0, 3, //-z
    7, 4, 5, 6, //+z
    6, 5, 1, 2, //+x
    3, 0, 4, 7, //-x
    2, 3, 7, 6, //+y
};

static u32 vertex_idxs[] = {
    0, 1, 2, 0, 2, 3
};

static void insert_vertex_data(f32* data, Tile* tile, i32* count)
{
    /* c = count, s = side, v = vertex */
    int c = *count;
    for (i32 s = 0; s < NUM_WALL_SIDES; s++) {
        for (i32 v = 0; v < VERTEX_COUNT; v++) {
            data[5*6*6*c+6*6*s+6*v]   = s_vertices[3*side_idxs[4*s+vertex_idxs[v]]]   + tile->pos.x;
            data[5*6*6*c+6*6*s+6*v+1] = s_vertices[3*side_idxs[4*s+vertex_idxs[v]]+1] * tile->pos.y;
            data[5*6*6*c+6*6*s+6*v+2] = s_vertices[3*side_idxs[4*s+vertex_idxs[v]]+2] + tile->pos.z;
            data[5*6*6*c+6*6*s+6*v+3] = tile->r;
            data[5*6*6*c+6*6*s+6*v+4] = tile->g;
            data[5*6*6*c+6*6*s+6*v+5] = tile->b;
        }
    }
    (*count)++;
}

void tilemap_init(void) 
{
    tilemap.tile_count = 0;
    for (i32 i = 0; i < TILEMAP_WIDTH * TILEMAP_WIDTH; i++) {
        if (i % 7 == 0)
            tilemap.map[i/TILEMAP_WIDTH][i%TILEMAP_WIDTH] = tile_create(i/TILEMAP_WIDTH, 3, i%TILEMAP_WIDTH, 0.5f, 0.5f, 0.5f), tilemap.tile_count++;
        else
            tilemap.map[i/TILEMAP_WIDTH][i%TILEMAP_WIDTH] = NULL;
    }
}

void tilemap_clear(void)
{
    for (i32 i = 0; i < TILEMAP_WIDTH * TILEMAP_WIDTH; i++)
        if (tilemap.map[i/TILEMAP_WIDTH][i%TILEMAP_WIDTH] != NULL)
            free(tilemap.map[i/TILEMAP_WIDTH][i%TILEMAP_WIDTH]);
}

void** tilemap_vertex_data(void) 
{
    void** data_signature = malloc(sizeof(void*));
    size_t* data_size = malloc(sizeof(size_t));
    *data_size = NUM_WALL_SIDES * VERTEX_COUNT * FIELD_COUNT * tilemap.tile_count * sizeof(f32);
    f32* data = malloc(*data_size);
    i32 count = 0;
    for (i32 i = 0; i < TILEMAP_WIDTH; i++)
        for (i32 j = 0; j < TILEMAP_WIDTH; j++)
            if (tilemap.map[i][j] != NULL)
                insert_vertex_data(data, tilemap.map[i][j], &count);
    data_signature[0] = (size_t*)data_size;
    data_signature[1] = (f32*)data;
    return data_signature;
}