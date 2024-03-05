#ifndef TILEMAP_H
#define TILEMAP_H

#include <gtype.h>
#include "tile.h"

#define TILEMAP_WIDTH 10

typedef struct TileMap {
    Tile* map[TILEMAP_WIDTH][TILEMAP_WIDTH];
    u32 tile_count;
} TileMap;

extern TileMap tilemap;

void tilemap_init(void);
void tilemap_clear(void);
f32* tilemap_vertex_data(void);

#endif