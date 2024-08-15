#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "../../util/array.h"
#include "../../util/type.h"
#include "../../util/vec.h"
#include "../../util/indices.h"
#include "../../util/constants.h"
#include "../particle/particle.h"
#include "../parjicle/parjicle.h"

typedef struct {
    f32 speed, scale, lifetime, rotation, hitbox_radius, timer;
    u32 tex, id, damage;
    u8 friendly;
    vec3f position, direction;
} Projectile;

Projectile* projectile_create(u32 id, u8 friendly);
void projectile_update(Projectile* projectile, f32 dt);
void projectile_destroy(Projectile* projectile, u32 idx);
void destroy_all_projectiles(void);

_ARRAY_DECLARE(Projectile, projectile)
extern ProjectileArray projectiles;

#define MAX_PROJECTILE_ID 1
#define SWORD 0

#define _PROJECTILE_INIT(_type) \
    void _type##_update(Projectile *projectile, f32 dt);

_PROJECTILE_INIT(sword)

#endif