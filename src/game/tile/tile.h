#ifndef TILE_H
#define TILE_H

#include "../../util/type.h"
#include "../../util/vec.h"

typedef enum { FLOOR, WALL1 } tiletype;

typedef struct {
    vec2i position;
    tiletype type;
} Tile;

Tile* tile_create(tiletype type);
void tile_destroy(Tile* tile);

#endif