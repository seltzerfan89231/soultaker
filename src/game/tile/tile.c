#include "tile.h"
#include <stdlib.h>

Tile* tile_create(tiletype type)
{
    Tile* tile = malloc(sizeof(Tile));
    tile->type = type;
    return tile;
}

void tile_destroy(Tile* tile)
{
    free(tile);
}