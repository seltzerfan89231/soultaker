#ifndef TILE_H
#define TILE_H

#include "../../util/type.h"
#include "../../util/vec.h"

typedef enum tiletype { FLOOR, WALL } tiletype;

typedef struct {
    vec3f position;
    vec2f tex;
    tiletype type;
} Tile;

Tile* tile_create(tiletype type);
void tile_push_data(Tile* tile, f32* buffer, u32 offset);
void tile_remove_data(Tile* tile, f32* buffer, u32 offset);
void tile_destroy(Tile* tile);

#endif