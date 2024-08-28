#ifndef TILE_H
#define TILE_H

#include "../../util/array.h"
#include "../../util/type.h"
#include "../../util/vec.h"
#include "../../util/indices.h"
#include "../entity/entity.h"

typedef struct {
    struct {
        i32 x, z;
    } position;
    struct {
        i32 w, l;
    } dimensions;
    u32 id, tex;
    f32 timer;
    bool interactable;
} Tile;

Tile* tile_create(u32 id, i32 x, i32 z, i32 w, i32 l);
void tile_update(Tile *tile, f32 dt);
void tile_interact(Tile *tile, Entity *entity);
void tile_destroy(Tile* tile, u32 idx);
void destroy_all_tiles(void);

_ARRAY_DECLARE(Tile, tile)
extern TileArray global_tiles;
extern TileArray interactable_tiles;

#define MAX_TILE_ID 2
#define GRASS 0
#define HELLSTONE 1

#define _TILE_INIT(_type) \
    void _type##_create(Tile *tile); \
    void _type##_update(Tile *tile, f32 dt); \
    void _type##_interact(Tile *tile, Entity *entity);

_TILE_INIT(grass)
_TILE_INIT(hellstone)

#endif