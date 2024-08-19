#include "tile.h"
#include "../tilemap/tilemap.h"
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
    tilemap_insert_tile(tile);
    return tile;
}

void tile_destroy(Tile* tile, u32 idx)
{
    assert(tile == tiles.buffer[idx]);
    tile_array_cut(&tiles, idx);
    free(tile);
}

void destroy_all_tiles(void)
{
    for (i32 i = 0; i < tiles.length; i++)
        free(tiles.buffer[i]);
    tile_array_destroy(&tiles);
}

_ARRAY_DEFINE(Tile, tile)