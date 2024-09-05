#include "aoe.h"
#include <stdlib.h>

AOEArray global_aoes;

AOE* aoe_create(f32 x, f32 z)
{
    AOE* aoe = malloc(sizeof(AOE));
    aoe->position.x = x;
    aoe->position.z = z;
    aoe->radius = 2.5;
    aoe->timer = 0;
    for (i32 i = 0; i < 20; i++) {
        Particle* part = particle_create();
        part->position.x = aoe->position.x + aoe->radius * cos(2 * i * PI / 20);
        part->position.y = 0.2;
        part->position.z = aoe->position.z + aoe->radius * sin(2 * i * PI / 20);
        part->color.b = 1.0f;
        part->scale = 0.25;
        part->lifetime = 999;
    }
    aoe_array_push(&global_aoes, aoe);
    return aoe;
}

void aoe_update_timer(AOE* aoe, f32 dt)
{
    aoe->timer -= dt;
}

void aoe_update(AOE* aoe)
{
    if (aoe->timer < 0)
        aoe->timer = 0.1;
}

void aoe_hit(AOE* aoe, Entity* entity)
{
    vec2f aoe_pos, ent_pos;
    aoe_pos = vec2f_create(aoe->position.x, aoe->position.z);
    ent_pos = vec2f_create(entity->position.x, entity->position.z);
    if (aoe->timer < 0 && vec2f_mag(vec2f_sub(aoe_pos, ent_pos)) < aoe->radius + entity->hitbox_radius)
        entity_damage(entity, 1);
}

void aoe_destroy(AOE* aoe, u32 idx)
{
    free(aoe);
}

void destroy_all_aoes(void)
{
    for (i32 i = 0; i < global_aoes.length; i++)
        free(global_aoes.buffer[i]);
    aoe_array_destroy(&global_aoes);
}

_ARRAY_DEFINE(AOE, aoe)