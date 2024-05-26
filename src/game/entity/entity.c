#include "entity.h"
#include <stdlib.h>

Entity* entity_create(entitytype type, bool friendly)
{
    Entity* entity = malloc(sizeof(Entity));
    entity->type = type;
    entity->scale = 1;
    entity->speed = 8;
    entity->lifetime = 5;
    entity->rotation = 0;
    entity->direction = vec3f_create(0, 0, 0);
    entity->friendly = friendly;
    entity->hitbox_radius = 0.5;
    return entity;
}

void entity_update_position(Entity* entity, f32 dt)
{
    entity->position = vec3f_add(entity->position, vec3f_scale(entity->speed * dt, entity->direction));
}

void entity_destroy(Entity* entity)
{
    free(entity);
}