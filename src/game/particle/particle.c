#include "particle.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

ParticleArray global_particles;

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
    particle_array_push(&global_particles, particle);
    return particle;
}

void particle_update(Particle* particle, f32 dt)
{
    particle->position = vec3f_add(particle->position, vec3f_scale(particle->speed * dt, particle->direction));
    particle->lifetime -= dt;
}

void particle_destroy(Particle *particle, u32 idx)
{
    assert(particle == global_particles.buffer[idx]);
    particle_array_cut(&global_particles, idx);
    free(particle);
}

void destroy_all_particles(void)
{
    for (i32 i = 0; i < global_particles.length; i++)
        free(global_particles.buffer[i]);
    particle_array_destroy(&global_particles);
}

_ARRAY_DEFINE(Particle, particle)