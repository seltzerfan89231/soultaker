#include "tile.h"
#include <stdlib.h>
#include <assert.h>

TileArray tiles;

#define _CREATE(_id, _lid) \
    case _id : _lid##_create(tile); break;

Tile* tile_create(u32 id, f32 x, f32 z)
{
    Tile* tile = malloc(sizeof(Tile));
    tile->id = id;
    tile->position.x = x;
    tile->position.z = z;
    switch (id) {
        _CREATE(GRASS, grass)
        _CREATE(HELLSTONE, hellstone)
    }
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