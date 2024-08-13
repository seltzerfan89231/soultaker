#include "entity.h"
#include "../player/player.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

EntityArray entities;

#define _ENTITY_CREATE(_id, _lid) \
    case _id : _lid##_create(entity); break;

Entity* entity_create(u32 id, u8 friendly)
{
    Entity* entity = malloc(sizeof(Entity));
    entity->id = id;
    entity->scale = 1;
    entity->speed = 1;
    entity->state = 0;
    entity->face_dir = TRUE;
    entity->timer = 0.0f;
    entity->timer2 = 0.0f;
    entity->flag = 0;
    entity->direction = vec3f_create(0, 0, 0);
    entity->facing = vec2f_create(1.0, 0.0);
    entity->friendly = friendly;
    entity->hitbox_radius = 0.5;
    entity->health = 100;
    entity->max_health = 100;
    switch (entity->id) {
        _ENTITY_CREATE(ENEMY, enemy)
        _ENTITY_CREATE(KNIGHT, knight)
        _ENTITY_CREATE(SLIME, slime)
    }
    entity_array_push(&entities, entity);
    return entity;
}

#define _ENTITY_UPDATE(_id, _lid) \
    case _id : _lid##_update(entity); break;

void entity_update(Entity* entity, f32 dt)
{
    entity->position = vec3f_add(entity->position, vec3f_scale(entity->speed * dt, entity->direction));
    switch (entity->id) {
        _ENTITY_UPDATE(ENEMY, enemy)
        _ENTITY_UPDATE(KNIGHT, knight)
        _ENTITY_UPDATE(SLIME, slime)
    }
    entity->timer += dt;
    entity->timer2 -= dt;
}

void entity_damage(Entity *entity, u32 damage)
{
    entity->health -= damage;
    if (entity->health < 0)
        entity->health = 0;
    printf("%d\n", entity->health);
}

void entity_set_direction(Entity *entity, vec3f direction)
{
    entity->direction = direction;
    if (entity->face_dir && vec3f_mag(direction) != 0)
        entity->facing.x = direction.x, entity->facing.y = direction.z;
}

#define _ENTITY_DIE(_id, _lid) \
    case _id : _lid##_die(entity); break;

void entity_destroy(Entity* entity, u32 idx)
{
    assert(entity == entities.buffer[idx]);
    switch (entity->id) {
        _ENTITY_DIE(ENEMY, enemy)
        _ENTITY_DIE(KNIGHT, knight)
        _ENTITY_DIE(SLIME, slime)
    }
    if (entity == player.entity)
        player.entity = NULL;
    entity_array_cut(&entities, idx);
    free(entity);
}

_ARRAY_DEFINE(Entity, entity)