#include "../weapon.h"

void sword_shoot(Weapon weapon, vec3f position, vec3f direction, vec3f target)
{
    f32 t = atan(direction.z / direction.x);
    Projectile* proj = projectile_create(SWORD_PROJ, TRUE, FALSE);
    proj->speed = 10;
    proj->position = position;
    proj->rotation = t + (direction.x > 0 ? 0 : PI);
    proj->direction = direction;
    proj->position.y = 0.5f;
}