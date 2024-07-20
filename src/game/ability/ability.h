#ifndef ABILITY_H
#define ABILITY_H

#include "../projectile/projectile.h"

typedef struct {
    u32 id, tex;
} Ability;

void ability_use(Ability ability, vec3f position, vec3f direction, vec3f target);

#define MAX_ABILITY_ID 1
#define SPELLBOMB  0

#define _ABILITY_INIT(_type) \
    void _type##_use(Ability ability, vec3f position, vec3f direction, vec3f target);

_ABILITY_INIT(spellbomb)

#endif