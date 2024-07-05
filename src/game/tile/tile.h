#ifndef TILE_H
#define TILE_H

#include "../../util/array.h"
#include "../../util/type.h"
#include "../../util/vec.h"

typedef enum { FLOOR, WALL1 } tiletype;

typedef struct {
    struct {
        i32 x, z;
    } position;
    tiletype type;
} Tile;

Tile* tile_create(tiletype type, f32 x, f32 z);
void tile_destroy(Tile* tile);

_ARRAY_DECLARE(Tile, tile)
extern TileArray tiles;

#endif