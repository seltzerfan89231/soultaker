#ifndef TILE_H
#define TILE_H

#include <gtype.h>
#include <gvec.h>

#define NUM_WALL_SIDES 5
#define NUM_FLOOR_SIDES 1
#define VERTEX_COUNT 6
#define FIELD_COUNT 6

typedef enum tiletype { FLOOR, WALL } tiletype;

typedef struct Tile {
    tiletype type;
} Tile;

Tile* tile_create(tiletype type);
void tile_destroy(Tile* tile);
void tile_vertex_data(vec3f pos, vec3f color, f32* buffer, Tile* tile, i32 offset);

#endif