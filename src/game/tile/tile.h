#ifndef TILE_H
#define TILE_H

#include "../../util/array.h"
#include "../../util/type.h"
#include "../../util/vec.h"
#include "../../util/indices.h"
#include "../entity/entity.h"

#define TILE_UP_LEFT    0
#define TILE_UP         1
#define TILE_UP_RIGHT   2
#define TILE_LEFT       3
#define TILE_NONE       4
#define TILE_RIGHT      5
#define TILE_DOWN_LEFT  6
#define TILE_DOWN       7
#define TILE_DOWN_RIGHT 8

typedef struct {
    struct {
        i32 x, z;
    } position;
    u32 id, tex;
    // 4 bits
    u8 shadow;
    // 4 bits
    u8 offset;
    // 2 bits
    u8 rotation;
    bool interactable;
} Tile;

Tile* tile_create(u32 id, i32 x, i32 z);
void tile_update_timer(f32 dt);
void tile_interact(Tile *tile, Entity *entity);
void tile_destroy(Tile* tile, u32 idx);
void destroy_all_tiles(void);

void tile_set_shadow(Tile *tile, u8 side);
void tile_set_offset(Tile *tile, u8 offset);
void tile_set_interactable(Tile *tile, bool val);
u8 tile_get_shadow(Tile *tile);
u8 tile_get_offset(Tile *tile);
u8 tile_get_interactable(Tile *tile);

_ARRAY_DECLARE(Tile, tile)
extern TileArray global_tiles;
extern f32 tile_timer;

#define MAX_TILE_ID 5
#define GRASS 0
#define HELLSTONE 1
#define SHAITAN_LAVA 2
#define SHAITAN_FLOOR 3
#define SHAITAN_HELLSTONE 4

#define _TILE_INIT(_type) \
    void _type##_create(Tile *tile); \
    void _type##_interact(Tile *tile, Entity *entity);

_TILE_INIT(grass)
_TILE_INIT(hellstone)
_TILE_INIT(shaitan_lava)
_TILE_INIT(shaitan_floor)
_TILE_INIT(shaitan_hellstone)

#endif