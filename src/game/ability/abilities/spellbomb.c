#include "../ability.h"

void spellbomb_use(Ability ability, vec3f position, vec3f direction, vec3f target)
{
    for (i32 i = 0; i < 18; i++) {
        Projectile* proj = projectile_create(SWORD_PROJ, TRUE, FALSE);
        proj->speed = 10;
        proj->position = target;
        proj->rotation = PI / 9 * i;
        proj->direction = vec3f_create(cos(proj->rotation), 0, sin(proj->rotation));
        proj->position.y = 0.5f;
    }
}