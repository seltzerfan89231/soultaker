#include "weapon.h"

#define _SHOOT(_id, _lid) \
    case _id : _lid##_shoot(weapon, position, direction, target); break;

void weapon_shoot(Weapon weapon, vec3f position, vec3f direction, vec3f target)
{
    switch (weapon.id) {
        _SHOOT(SWORD, sword)
        _SHOOT(SWORD2, sword2)
    }
}