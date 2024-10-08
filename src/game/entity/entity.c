#include "entity.h"
#include "../player/player.h"
#include "../aud/aud.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

EntityArray global_entities;
Entity* boss;

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
    entity->data = NULL;
    entity->flag = 0;
    entity->phase = 0;
    entity->ground_level = TRUE;
    entity->invisible = FALSE;
    entity->direction = vec3f_create(0, 0, 0);
    entity->facing = vec2f_create(1.0, 0.0);
    entity->friendly = friendly;
    entity->hitbox_radius = 0.5;
    entity->health = 100;
    entity->invulnerable = FALSE;
    entity->max_health = 100;
    switch (entity->id) {
        _ENTITY_CREATE(ENEMY, enemy)
        _ENTITY_CREATE(KNIGHT, knight)
        _ENTITY_CREATE(SLIME, slime)
        _ENTITY_CREATE(TRAINING_DUMMY, training_dummy)
        _ENTITY_CREATE(SHAITAN_THE_ADVISOR, shaitan_the_advisor);
        _ENTITY_CREATE(SHAITAN_HAND, shaitan_hand)
    }
    entity_array_push(&global_entities, entity);
    return entity;
}

#define _ENTITY_UPDATE(_id, _lid) \
    case _id : _lid##_update(entity, dt); break;

void entity_update(Entity* entity, f32 dt)
{
    entity->position = vec3f_add(entity->position, vec3f_scale(entity->speed * dt, entity->direction));
    if (entity->ground_level)
        entity->position.y = 0;
    else
        entity->ground_level = TRUE;
    switch (entity->id) {
        _ENTITY_UPDATE(ENEMY, enemy)
        _ENTITY_UPDATE(KNIGHT, knight)
        _ENTITY_UPDATE(SLIME, slime)
        _ENTITY_UPDATE(TRAINING_DUMMY, training_dummy)
        _ENTITY_UPDATE(SHAITAN_THE_ADVISOR, shaitan_the_advisor)
        _ENTITY_UPDATE(SHAITAN_HAND, shaitan_hand)
    }
}

#define _ENTITY_DAMAGE(_id, _lid) \
    case _id : _lid##_damage(entity, damage); break;

void entity_damage(Entity *entity, f32 damage)
{
    if (entity->invulnerable)
        return;
    aud_play(GUI_CLICK_AUD);
    switch (entity->id) {
        _ENTITY_DAMAGE(TRAINING_DUMMY, training_dummy)
        _ENTITY_DAMAGE(SHAITAN_THE_ADVISOR, shaitan_the_advisor)
        default:
            entity->health -= damage;
            if (entity->health < 0)
                entity->health = 0;
    }
    
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
    assert(entity == global_entities.buffer[idx]);
    switch (entity->id) {
        _ENTITY_DIE(ENEMY, enemy)
        _ENTITY_DIE(KNIGHT, knight)
        _ENTITY_DIE(SLIME, slime)
        _ENTITY_DIE(TRAINING_DUMMY, training_dummy)
        _ENTITY_DIE(SHAITAN_THE_ADVISOR, shaitan_the_advisor)
        _ENTITY_DIE(SHAITAN_HAND, shaitan_hand)
    }
    if (entity == player.entity)
        player.entity = NULL;
    entity_array_cut(&global_entities, idx);
    free(entity->data);
    free(entity);
}

void destroy_all_entities(void)
{
    for (i32 i = 0; i < global_entities.length; i++) {
        free(global_entities.buffer[i]->data);
        free(global_entities.buffer[i]);
    }   
    entity_array_destroy(&global_entities);
}

void entity_connect(Entity* entity1, Entity* entity2)
{

}

_ARRAY_DEFINE(Entity, entity)