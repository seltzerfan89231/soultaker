#include "tilemap.h"

TileMap tilemap;

void tilemap_init(void)
{
    for (i32 i = 0; i < 100; i++)
        tilemap.map[i/10][i%10] = tile_create(i);
}