#ifndef TILE_H
#define TILE_H

#include "../../util/type.h"
#include "../../util/vec.h"
#include "../../util/vertex_data.h"

typedef enum tiletype { FLOOR, WALL } tiletype;

typedef struct Tile {
    vec2f position;
    vec2f tex;
    f32 height;
    tiletype type;
} Tile;

Tile* tile_create(tiletype type);
void tile_vertex_data(Tile* tile, f32* buffer, u32* offset);
void tile_destroy(Tile* tile);

#endif