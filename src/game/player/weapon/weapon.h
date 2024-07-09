#ifndef WEAPON_H
#define WEAPON_H

#include "../../projectile/projectile.h"

typedef struct {
    u32 id, tex;
} Weapon;

void weapon_shoot(Weapon weapon, vec3f position, vec3f direction);

#define MAX_WEAPON_ID 2
#define SWORD  0
#define SWORD2 1

#define _WEAPON_INIT(_type) \
    void _type##_shoot(Weapon weapon, vec3f position, vec3f direction);

_WEAPON_INIT(sword)
_WEAPON_INIT(sword2)

#endif