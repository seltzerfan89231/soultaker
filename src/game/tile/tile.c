#include "tile.h"
#include <stdlib.h>

Tile* tile_create(tiletype type)
{
    Tile* tile = malloc(sizeof(Tile));
    tile->type = type;
    tile->tex = vec2f_create(0.25f, 0.0f);
    return tile;
}

void tile_push_data(Tile* tile, f32* buffer, u32 offset)
{
    buffer[offset++] = tile->position.x;
    buffer[offset++] = tile->position.y;
    buffer[offset++] = tile->position.z;
}

void tile_remove_data(Tile* tile, f32* buffer, u32 offset)
{
    buffer[offset++] = 0;
    buffer[offset++] = 0;
    buffer[offset++] = 0;
}

void tile_destroy(Tile* tile)
{
    free(tile);
}