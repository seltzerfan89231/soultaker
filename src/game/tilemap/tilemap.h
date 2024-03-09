#ifndef TILEMAP_H
#define TILEMAP_H

#include <gtype.h>
#include "../deque.h"
#include "tile.h"

#define TILEMAP_WIDTH 100

typedef struct TileMap {
    Tile* map[TILEMAP_WIDTH][TILEMAP_WIDTH];
    Deque deque;
    i32 faces;
} TileMap;

extern TileMap tilemap;

void tilemap_init(void);
void tilemap_clear(void);
void tilemap_remove(Tile* tile);
void tilemap_insert(Tile* tile);
void tilemap_vertex_data(f32* data, i32* offset);
size_t tilemap_data_size(void);

#endif