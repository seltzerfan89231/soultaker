#ifndef TILE_H
#define TILE_H

#include <gtype.h>
#include <gvec.h>

typedef struct Tile {
    f32 r, g, b;
} Tile;

Tile* tile_create(f32 r, f32 g, f32 b);

#endif