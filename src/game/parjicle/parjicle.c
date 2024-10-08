#include "parjicle.h"
#include <stdlib.h>
#include <assert.h>

ParjicleArray global_parjicles;

Parjicle* parjicle_create(f32 rotation)
{
    Parjicle *parjicle = malloc(sizeof(Parjicle));
    parjicle->scale = 0.5f;
    parjicle->lifetime = 1.0f;
    parjicle->speed = 1.0f;
    parjicle->direction = vec3f_create(0.0f, 0.0f, 0.0f);
    parjicle->rotation = rotation;
    parjicle->color.r = 0;
    parjicle->color.g = 0;
    parjicle->color.b = 1;
    parjicle_array_push(&global_parjicles, parjicle);
    return parjicle;
}

void parjicle_update(Parjicle* parjicle, f32 dt)
{
    parjicle->position = vec3f_add(parjicle->position, vec3f_scale(parjicle->speed * dt, parjicle->direction));
    parjicle->lifetime -= dt;
}

void parjicle_destroy(Parjicle *parj, u32 idx)
{
    assert(parj == global_parjicles.buffer[idx]);
    parjicle_array_cut(&global_parjicles, idx);
    free(parj);
}

void destroy_all_parjicles(void)
{
    for (i32 i = 0; i < global_parjicles.length; i++)
        free(global_parjicles.buffer[i]);
    parjicle_array_destroy(&global_parjicles);
}

_ARRAY_DEFINE(Parjicle, parjicle)