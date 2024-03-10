#ifndef TILE_H
#define TILE_H

#include <gtype.h>
#include <gvec.h>
#include "../data_structures/dll.h"

#define NUM_WALL_SIDES 5
#define NUM_FLOOR_SIDES 1
#define VERTEX_COUNT 6
#define FIELD_COUNT 6

typedef enum tiletype {
    FLOOR, WALL
} tiletype;

typedef struct Tile {
    vec3i pos;
    f32 r, g, b;
    tiletype type;
} Tile;

Tile* tile_create(i32 x, i32 y, i32 z, f32 r, f32 g, f32 b, tiletype type);
void tile_destroy(Tile* tile);
void tile_vertex_data(f32* buffer, Tile* tile, i32 offset);

#endif