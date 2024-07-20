#include "ability.h"

#define _USE(_id, _lid) \
    case _id : _lid##_use(ability, position, direction, target); break;

void ability_use(Ability ability, vec3f position, vec3f direction, vec3f target)
{
    switch (ability.id) {
        _USE(SPELLBOMB, spellbomb)
    }
}