#include "aoe.h"
#include <stdlib.h>

AOEArray global_aoes;

AOE* aoe_create(f32 x, f32 z, bool friendly)
{
    AOE* aoe = malloc(sizeof(AOE));
    aoe->position.x = x;
    aoe->position.z = z;
    aoe->radius = 2.5;
    aoe->friendly = friendly;
    /* for (i32 i = 0; i < 20; i++) {
        Particle* part = particle_create();
        f32 theta = 2.0 * i * PI / 20;
        part->position.x = aoe->position.x + aoe->radius * cos(theta);
        part->position.y = 0.2;
        part->position.z = aoe->position.z + aoe->radius * sin(theta);
        part->direction.x = cos(theta);
        part->direction.z = sin(theta);
        part->speed = 1;
        part->color.b = 1.0f;
        part->scale = 0.25;
        part->lifetime = 1;
    } */
    for (i32 i = 0; i < 20; i++) {
        f32 theta = 2.0 * i * PI / 20;
        Parjicle* parj = parjicle_create(theta);
        parj->position.x = aoe->position.x;
        parj->position.y = 0.2;
        parj->position.z = aoe->position.z;
        parj->direction.x = cos(theta);
        parj->direction.z = sin(theta);
        parj->speed = 8;
        parj->color.b = 1.0f;
        parj->scale = 0.25;
        parj->lifetime = aoe->radius / parj->speed;
    }
    aoe_array_push(&global_aoes, aoe);
    return aoe;
}

void aoe_destroy(AOE* aoe, u32 idx)
{
    assert(aoe == global_aoes.buffer[idx]);
    aoe_array_cut(&global_aoes, idx);
    free(aoe);
}

void destroy_all_aoes(void)
{
    for (i32 i = 0; i < global_aoes.length; i++)
        free(global_aoes.buffer[i]);
    aoe_array_destroy(&global_aoes);
}

_ARRAY_DEFINE(AOE, aoe)