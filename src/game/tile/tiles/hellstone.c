#include "../tile.h"

void hellstone_create(Tile *tile)
{
    tile->tex = HELLSTONE_TEX;
    tile_set_interactable(tile, TRUE);
}

void hellstone_interact(Tile *tile, Entity *entity)
{
    entity->ground_level = FALSE;
    entity->position.y = -0.5;
    if (tile_timer < 0)
        entity_damage(entity, 1);
}