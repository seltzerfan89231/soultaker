#include "entity.h"
#include <stdlib.h>
#include <stdio.h>

u32 **frames;

Entity* entity_create(u32 id, u8 friendly)
{
    Entity* entity = malloc(sizeof(Entity));
    entity->id = id;
    entity->scale = 1;
    entity->speed = 8;
    if (entity->id == KNIGHT)
        entity->state = KNIGHT_IDLE;
    if (entity->id == ENEMY)
        entity->state = ENEMY_IDLE;
    entity->face_dir = TRUE;
    entity->timer = 0.0f;
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
    
    if (vec3f_mag(entity->direction) == 0) {
        if (entity->state == KNIGHT_WALK_1 || entity->state == KNIGHT_WALK_2)
            entity->state = KNIGHT_IDLE;
    }
    else {
        if (entity->state == KNIGHT_IDLE)
            entity->state = KNIGHT_WALK_1;
    }

    switch (entity->state) {
        case KNIGHT_WALK_1:
            if (entity->timer > 0.15) {
                entity->timer = 0;
                entity->state = KNIGHT_WALK_2;
            }
            break;
        case KNIGHT_WALK_2:
            if (entity->timer > 0.15) {
                entity->timer = 0;
                entity->state = KNIGHT_WALK_1;
            }
            break;
        case KNIGHT_SHOOT_1:
            if (entity->timer > 0.15) {
                entity->timer = 0;
                entity->state = KNIGHT_SHOOT_2;
            }
            break;
        case KNIGHT_SHOOT_2:
            if (entity->timer > 0.15) {
                entity->timer = 0;
                entity->state = KNIGHT_SHOOT_1;
            }
            break;
        default:
            break;
    }

    entity->timer += dt;
}

void entity_set_state(Entity *entity, u32 state)
{
    switch (state) {
        case KNIGHT_SHOOT_1:
            entity->face_dir = FALSE;
            if (entity->state != KNIGHT_SHOOT_1 && entity->state != KNIGHT_SHOOT_2) {
                entity->state = state;
                entity->timer = 0;
            }
            break;
        case KNIGHT_IDLE:
            if (entity->state == KNIGHT_WALK_1 || entity->state == KNIGHT_WALK_2)
                break;
        default:
            entity->state = state;
            entity->face_dir = TRUE;
            break;
    }
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