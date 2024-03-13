#ifndef TILE_H
#define TILE_H

#include <gtype.h>
#include <gvec.h>

typedef enum tiletype { FLOOR, WALL } tiletype;

typedef struct Tile {
    tiletype type;
} Tile;

Tile* tile_create(tiletype type);
void tile_destroy(Tile* tile);

#endif