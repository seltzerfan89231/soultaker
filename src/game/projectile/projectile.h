#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "../../util/type.h"
#include "../../util/vec.h"
#include "../../util/constants.h"

typedef enum { ONE } projtype;

typedef struct {
    f32 speed, scale, lifetime, rotation, hitbox_radius;
    bool friendly;
    projtype type;
    vec3f position, direction;
    vec2f tex;
} Projectile;

Projectile* projectile_create(projtype type, bool friendly);
void projectile_update_position(Projectile* projectile, f32 dt);
void projectile_destroy(Projectile* projectile);

#endif