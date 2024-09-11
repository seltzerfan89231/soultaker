#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "../../util/array.h"
#include "../../util/type.h"
#include "../../util/vec.h"
#include "../../util/indices.h"
#include "../../util/constants.h"
#include "../entity/entity.h"
#include "../particle/particle.h"
#include "../parjicle/parjicle.h"

typedef struct {
    f32 speed, scale, lifetime, rotation, rot_speed, hitbox_radius, timer;
    u32 tex, id, damage;
    vec3f position, direction;
    bool pierce, friendly, tilt_tex;
    EntityArray *hit_entities;
} Projectile;

Projectile* projectile_create(u32 id, bool friendly, bool pierce);
void projectile_update(Projectile* projectile, f32 dt);
bool projectile_hit(Projectile* projectile, Entity *entity, u32 idx);
void projectile_destroy(Projectile* projectile, u32 idx);
void destroy_all_projectiles(void);

_ARRAY_DECLARE(Projectile, projectile)
extern ProjectileArray global_projectiles;

#define MAX_PROJECTILE_ID 3
#define DEFAULT_PROJ 0
#define SWORD_PROJ 1

#define _PROJECTILE_INIT(_type) \
    void _type##_update(Projectile *projectile, f32 dt);

_PROJECTILE_INIT(sword_proj)
#endif