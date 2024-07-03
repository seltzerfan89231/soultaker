#include "entity.h"
#include <stdlib.h>
#include <stdio.h>

Entity* entity_create(u32 id, u8 friendly)
{
    Entity* entity = malloc(sizeof(Entity));
    entity->id = id;
    entity->scale = 1;
    entity->speed = 8;
    entity->state = 0;
    entity->face_dir = TRUE;
    entity->timer = 0.0f;
    entity->flag = 0;
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
    if (entity->id == ENEMY)
        return;
    if (entity->id == KNIGHT)
        knight_update_state(entity);
    entity->timer += dt;
}

void entity_set_direction(Entity *entity, vec3f direction)
{
    entity->direction = direction;
    if (entity->face_dir && vec3f_mag(direction) != 0)
        entity->facing.x = direction.x, entity->facing.y = direction.z;
}

void entity_destroy(Entity* entity)
{
    free(entity);
}

_ARRAY_DEFINE(Entity, entity)