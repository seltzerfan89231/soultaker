#include "tile.h"
#include <stdlib.h>

TileArray tiles;

Tile* tile_create(tiletype type, f32 x, f32 z)
{
    Tile* tile = malloc(sizeof(Tile));
    tile->type = type;
    tile->position.x = x;
    tile->position.z = z;
    return tile;
}

void tile_destroy(Tile* tile)
{
    free(tile);
}

_ARRAY_DEFINE(Tile, tile)