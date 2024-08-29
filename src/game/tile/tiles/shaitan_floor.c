#include "../tile.h"

void shaitan_floor_create(Tile *tile)
{
    switch (rand() % 2) {
        case 0:
            tile->tex = SHAITAN_FLOOR_1_TEX; break;
        case 1:
            tile->tex = SHAITAN_FLOOR_2_TEX; break;
    }
}

void shaitan_floor_update(Tile *tile, f32 dt)
{

}

void shaitan_floor_interact(Tile *tile, Entity *entity)
{

}