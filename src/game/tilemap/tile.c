#include "tile.h"
#include <stdlib.h>

#define NUM_WALL_SIDES 5
#define NUM_TILE_SIDES 1
#define VERTEX_COUNT 6
#define FIELD_COUNT 6

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

Tile* tile_create(i32 x, i32 y, i32 z, f32 r, f32 g, f32 b)
{
    Tile* tile = malloc(sizeof(Tile));
    tile->pos = vec3i_create(x, y, z);
    tile->r = r;
    tile->g = g;
    tile->b = b;
    tile->node = node_create(tile);
    return tile;
}

void tile_destroy(Tile* tile)
{

}

void tile_vertex_data(f32* data, Tile* tile, i32* offset)
{
    for (i32 s = 0; s < NUM_WALL_SIDES; s++) {
        for (i32 v = 0; v < VERTEX_COUNT; v++) {
            data[(*offset)++] = s_vertices[3*side_idxs[4*s+vertex_idxs[v]]]   + tile->pos.x;
            data[(*offset)++] = s_vertices[3*side_idxs[4*s+vertex_idxs[v]]+1] * tile->pos.y;
            data[(*offset)++] = s_vertices[3*side_idxs[4*s+vertex_idxs[v]]+2] + tile->pos.z;
            data[(*offset)++] = tile->r + s * 0.1;
            data[(*offset)++] = tile->g + s * 0.1;
            data[(*offset)++] = tile->b + s * 0.1;
        }
    }
}