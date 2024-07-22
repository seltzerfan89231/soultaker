#include "particle.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

ParticleArray particles;

Particle* particle_create(void)
{
    Particle *particle = malloc(sizeof(Particle));
    particle->speed = 1.0f;
    particle->lifetime = 2.0f;
    particle->scale = 0.5f;
    particle->direction = vec3f_create(0.0f, 0.0f, 0.0f);
    particle->color.r = 0;
    particle->color.g = 0;
    particle->color.b = 1;
    particle_array_push(&particles, particle);
    return particle;
}

void particle_update(Particle* particle, f32 dt)
{
    particle->position = vec3f_add(particle->position, vec3f_scale(particle->speed * dt, particle->direction));
    particle->lifetime -= dt;
}

void particle_destroy(Particle *particle, u32 idx)
{
    assert(particle == particles.buffer[idx]);
    particle_array_cut(&particles, idx);
    free(particle);
}

_ARRAY_DEFINE(Particle, particle)