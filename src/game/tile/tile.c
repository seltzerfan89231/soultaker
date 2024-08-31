#include "tile.h"
#include "../tilemap/tilemap.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

TileArray global_tiles;
TileArray interactable_tiles;

#define _CREATE(_id, _lid) \
    case _id : _lid##_create(tile); break;

Tile* tile_create(u32 id, i32 x, i32 z, i32 w, i32 l)
{
    Tile* tile = malloc(sizeof(Tile));
    tile->id = id;
    tile->position.x = x;
    tile->position.z = z;
    tile->dimensions.w = w;
    tile->dimensions.l = l;
    tile->interactable = FALSE;
    tile->timer = 0;
    tile->shadow = 0;
    switch (id) {
        _CREATE(GRASS, grass)
        _CREATE(HELLSTONE, hellstone)
        _CREATE(SHAITAN_LAVA, shaitan_lava)
        _CREATE(SHAITAN_FLOOR, shaitan_floor)
        _CREATE(SHAITAN_HELLSTONE, shaitan_hellstone)
    }
    tile_array_push(&global_tiles, tile);
    if (tile->interactable)
        tile_array_push(&interactable_tiles, tile);
    tilemap_insert_tile(tile);
    return tile;
}

#define _UPDATE(_id, _lid) \
    case _id : _lid##_update(tile, dt); break;

void tile_update(Tile *tile, f32 dt)
{
    if (!tile->interactable)
        return;
    switch (tile->id) {
        _UPDATE(HELLSTONE, hellstone)
        _UPDATE(SHAITAN_LAVA, shaitan_lava)
    }
}

#define _INTERACT(_id, _lid) \
    case _id : _lid##_interact(tile, entity); break;

void tile_interact(Tile *tile, Entity *entity)
{
    if (!tile->interactable)
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
    tile_array_destroy(&interactable_tiles);
}

_ARRAY_DEFINE(Tile, tile)