#ifndef TILEMAP_H
#define TILEMAP_H

#include <gtype.h>
#include "tile.h"

typedef struct TileMap {
    Tile map[10][10];
} TileMap;

extern TileMap tilemap;

void tilemap_init(void);

#endif