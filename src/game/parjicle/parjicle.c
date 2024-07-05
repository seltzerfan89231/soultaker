#include "parjicle.h"
#include <stdlib.h>

ParjicleArray parjicles;

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
    parjicle_array_push(&parjicles, parjicle);
    return parjicle;
}

void parjicle_update(Parjicle* parjicle, f32 dt)
{
    parjicle->position = vec3f_add(parjicle->position, vec3f_scale(parjicle->speed * dt, parjicle->direction));
    parjicle->lifetime -= dt;
}

void parjicle_destroy(Parjicle *parj)
{
    free(parj);
}

_ARRAY_DEFINE(Parjicle, parjicle)