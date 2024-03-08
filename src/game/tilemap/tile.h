#ifndef TILE_H
#define TILE_H

#include <gtype.h>
#include <gvec.h>
#include "../deque.h"

typedef struct Tile {
    vec3i pos;
    f32 r, g, b;
    Node* node;
} Tile;

Tile* tile_create(i32 x, i32 y, i32 z, f32 r, f32 g, f32 b);
void tile_destroy(Tile* tile);
void tile_vertex_data(f32* data, Tile* tile, i32* offset);

#endif