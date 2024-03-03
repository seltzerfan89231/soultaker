#include "tile.h"
#include <stdlib.h>

Tile* tile_create(f32 r, f32 g, f32 b)
{
    Tile* tile = malloc(sizeof(Tile));
    tile->r = r;
    tile->g = g;
    tile->b = b;
    return tile;
}