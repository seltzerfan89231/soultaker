#ifndef TILE_H
#define TILE_H

#include <gtype.h>
#include <gvec.h>

typedef struct Tile {
    vec3i pos;
    f32 r, g, b;
} Tile;

Tile* tile_create(i32 x, i32 y, i32 z, f32 r, f32 g, f32 b);

#endif