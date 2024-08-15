#ifndef PARTICLE_H
#define PARTICLE_H

#include "../../util/array.h"
#include "../../util/type.h"
#include "../../util/vec.h"
#include "../../util/constants.h"

typedef struct {
    f32 speed, scale, lifetime;
    vec3f position, direction;
    struct {
        f32 r, g, b;
    } color;
} Particle;

Particle* particle_create(void);
void particle_update(Particle *particle, f32 dt);
void particle_destroy(Particle *particle, u32 idx);
void destroy_all_particles(void);

_ARRAY_DECLARE(Particle, particle)
extern ParticleArray particles;

#endif