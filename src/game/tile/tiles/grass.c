#include "../tile.h"

void grass_create(Tile *tile)
{
    switch (rand() % 3) {
        case 0:
            tile->tex = GRASS_1_TEX; break;
        case 1:
            tile->tex = GRASS_2_TEX; break;
        case 2:
            tile->tex = GRASS_3_TEX; break;
    }
}