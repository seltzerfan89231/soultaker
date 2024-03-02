#ifndef TILE_H
#define TILE_H

#include <gtype.h>

typedef struct Tile {
    i32 data;
} Tile;

Tile tile_create(i32 data);

#endif