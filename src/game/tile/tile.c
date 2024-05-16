#include "tile.h"
#include <stdlib.h>

Tile* tile_create(tiletype type)
{
    Tile* tile = malloc(sizeof(Tile));
    tile->type = type;
    return tile;
}

void tile_push_data(Tile* tile, f32* buffer, u32 offset)
{
    offset *= 2;
    buffer[offset++] = tile->position.x;
    buffer[offset++] = tile->position.y;
}

void tile_remove_data(Tile* tile, f32* buffer, u32 offset)
{
    offset *= 2;
    buffer[offset++] = 0;
    buffer[offset++] = 0;
}

void tile_destroy(Tile* tile)
{
    free(tile);
}