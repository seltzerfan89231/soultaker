#include "tile.h"
#include "../tilemap/tilemap.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

TileArray global_tiles;
TileArray interactable_tiles;

#define _CREATE(_id, _lid) \
    case _id : _lid##_create(tile); break;

Tile* tile_create(u32 id, f32 x, f32 z)
{
    Tile* tile = malloc(sizeof(Tile));
    tile->id = id;
    tile->position.x = x;
    tile->position.z = z;
    tile->interactable = FALSE;
    tile->timer = 0;
    switch (id) {
        _CREATE(GRASS, grass)
        _CREATE(HELLSTONE, hellstone)
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