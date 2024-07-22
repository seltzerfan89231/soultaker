#include "tile.h"
#include <stdlib.h>
#include <assert.h>

TileArray tiles;

Tile* tile_create(tiletype type, f32 x, f32 z)
{
    Tile* tile = malloc(sizeof(Tile));
    tile->type = type;
    tile->position.x = x;
    tile->position.z = z;
    tile->tex = TILE_TEX;
    tile_array_push(&tiles, tile);
    return tile;
}

void tile_destroy(Tile* tile, u32 idx)
{
    assert(tile == tiles.buffer[idx]);
    tile_array_cut(&tiles, idx);
    free(tile);
}

_ARRAY_DEFINE(Tile, tile)