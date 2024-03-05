#include "tile.h"
#include <stdlib.h>

Tile* tile_create(i32 x, i32 y, i32 z, f32 r, f32 g, f32 b)
{
    Tile* tile = malloc(sizeof(Tile));
    tile->pos = vec3i_create(x, y, z);
    tile->r = r;
    tile->g = g;
    tile->b = b;
    return tile;
}