#include "tile.h"
#include "../tilemap/tilemap.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

TileArray global_tiles;
f32 tile_timer;

#define _CREATE(_id, _lid) \
    case _id : _lid##_create(tile); break;

Tile* tile_create(u32 id, i32 x, i32 z)
{
    Tile* tile = malloc(sizeof(Tile));
    tile->id = id;
    tile->position.x = x;
    tile->position.z = z;
    tile->interactable = FALSE;
    tile->shadow = 0;
    tile->offset = 0;
    switch (id) {
        _CREATE(GRASS, grass)
        _CREATE(HELLSTONE, hellstone)
        _CREATE(SHAITAN_LAVA, shaitan_lava)
        _CREATE(SHAITAN_FLOOR, shaitan_floor)
        _CREATE(SHAITAN_HELLSTONE, shaitan_hellstone)
    }
    tile_array_push(&global_tiles, tile);
    tilemap_insert_tile(tile);
    return tile;
}

void tile_update_timer(f32 dt)
{
    if (tile_timer < 0)
        tile_timer = 0.1;
    tile_timer -= dt;
}

void tile_set_shadow(Tile *tile, u8 side)
{
    tile->shadow |= (1 << side);
}

void tile_set_offset(Tile *tile, u8 offset)
{
    tile->offset = offset;
}

void tile_set_interactable(Tile *tile, bool val)
{
    tile->interactable = val;
}

u8 tile_get_shadow(Tile *tile)
{
    return tile->shadow;
}

u8 tile_get_offset(Tile *tile)
{
    return tile->offset;
}

u8 tile_get_interactable(Tile *tile)
{
    return tile->interactable;
}

#define _INTERACT(_id, _lid) \
    case _id : _lid##_interact(tile, entity); break;

void tile_interact(Tile *tile, Entity *entity)
{
    if (!tile_get_interactable(tile))
        return;
    switch (tile->id) {
        _INTERACT(HELLSTONE, hellstone)
        _INTERACT(SHAITAN_LAVA, shaitan_lava)
    }
}

void tile_destroy(Tile* tile, u32 idx)
{
    assert(tile == global_tiles.buffer[idx]);
    tile_array_cut(&global_tiles, idx);
    free(tile);
}

void destroy_all_tiles(void)
{
    for (i32 i = 0; i < global_tiles.length; i++)
        free(global_tiles.buffer[i]);
    tile_array_destroy(&global_tiles);
}

_ARRAY_DEFINE(Tile, tile)