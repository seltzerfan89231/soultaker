#include "tile.h"

Tile tile_create(i32 data)
{
    Tile tile;
    tile.data = data;
    return tile;
}