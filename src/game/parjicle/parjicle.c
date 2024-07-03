#include "parjicle.h"
#include <stdlib.h>

Parjicle *parjicle_create(f32 rotation)
{
    Parjicle *parjicle = malloc(sizeof(Parjicle));
    parjicle->scale = 0.5f;
    parjicle->lifetime = 1.0f;
    parjicle->speed = 1.0f;
    parjicle->direction = vec3f_create(0.0f, 0.0f, 0.0f);
    parjicle->rotation = rotation;
    return parjicle;
}

void parjicle_update_position(Parjicle* parjicle, f32 dt)
{
    parjicle->position = vec3f_add(parjicle->position, vec3f_scale(parjicle->speed * dt, parjicle->direction));
    parjicle->lifetime -= dt;
}

void parjicle_destroy(Parjicle *parj)
{
    free(parj);
}

_ARRAY_DEFINE(Parjicle, parjicle)