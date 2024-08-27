#include "../tile.h"

void hellstone_create(Tile *tile)
{
    tile->tex = HELLSTONE_TEX;
    tile->interactable = TRUE;
}

void hellstone_update(Tile *tile, f32 dt)
{
    tile->timer -= dt;
}

void hellstone_interact(Tile *tile, Entity *entity)
{
    entity->ground_level = FALSE;
    entity->position.y = -0.5;
    if (tile->timer < 0) {
        tile->timer = 0.1;
        entity_damage(entity, 0.1);
    }
}