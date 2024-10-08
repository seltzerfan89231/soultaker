#include "../tile.h"

void shaitan_lava_create(Tile *tile)
{
    tile->tex = SHAITAN_LAVA_TEX;
    tile_set_interactable(tile, TRUE);
    tile_set_offset(tile, TILE_UP_LEFT);
}

void shaitan_lava_interact(Tile *tile, Entity *entity)
{
    entity->ground_level = FALSE;
    entity->position.y = -0.2;
    if (tile_timer >= 0)
        return;
    if (entity->id == SHAITAN_THE_ADVISOR || entity->id == SHAITAN_HAND)
        return;
    entity_damage(entity, 1);
}