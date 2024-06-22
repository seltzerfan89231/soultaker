#include "entity.h"
#include <stdlib.h>

Entity* entity_create(entitytype type, u8 friendly)
{
    Entity* entity = malloc(sizeof(Entity));
    entity->type = type;
    entity->scale = 1;
    entity->speed = 8;
    entity->lifetime = 5;
    entity->direction = vec3f_create(0, 0, 0);
    entity->friendly = friendly;
    entity->hitbox_radius = 0.5;
    entity->health = 100.0f;
    entity->max_health = 100.0f;
    return entity;
}

void entity_update(Entity* entity, f32 dt)
{
    entity->position = vec3f_add(entity->position, vec3f_scale(entity->speed * dt, entity->direction));
}

void entity_set_direction(Entity *entity, vec3f direction)
{
    entity->direction = direction;
    if (vec3f_mag(direction) != 0)
        entity->facing = direction;
}

void entity_destroy(Entity* entity)
{
    free(entity);
}