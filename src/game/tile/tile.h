#ifndef TILE_H
#define TILE_H

#include "../../util/array.h"
#include "../../util/type.h"
#include "../../util/vec.h"
#include "../../util/indices.h"

typedef struct {
    struct {
        i32 x, z;
    } position;
    u32 id, tex;
} Tile;

Tile* tile_create(u32 id, f32 x, f32 z);
void tile_destroy(Tile* tile, u32 idx);
void destroy_all_tiles(void);

_ARRAY_DECLARE(Tile, tile)
extern TileArray tiles;

#define MAX_TILE_ID 2
#define GRASS 0
#define HELLSTONE 1

#define _TILE_INIT(_type) \
    void _type##_create(Tile *tile);

_TILE_INIT(grass)
_TILE_INIT(hellstone)

#endif