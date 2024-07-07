#ifndef WEAPON_H
#define WEAPON_H

#include "../../projectile/projectile.h"

typedef struct {
    u32 id;
} Weapon;

void weapon_shoot(Weapon weapon, vec3f position, vec3f direction);

#define MAX_WEAPON_ID 1
#define SWORD 0

#define _WEAPON_INIT(_type) \
    void _type##_shoot(Weapon weapon, vec3f position, vec3f direction);

_WEAPON_INIT(sword)

#endif