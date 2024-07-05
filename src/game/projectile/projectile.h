#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "../../util/array.h"
#include "../../util/type.h"
#include "../../util/vec.h"
#include "../../util/constants.h"
#include "../particle/particle.h"
#include "../parjicle/parjicle.h"

typedef struct {
    f32 speed, scale, lifetime, rotation, hitbox_radius, timer;
    u8 friendly;
    vec3f position, direction;
} Projectile;

Projectile* projectile_create(u8 friendly);
void projectile_update(Projectile* projectile, f32 dt);
void projectile_destroy(Projectile* projectile);

_ARRAY_DECLARE(Projectile, projectile)

extern ProjectileArray projectiles;

void projectile_init(ProjectileArray *ptr);

#endif