#include "../weapon.h"

void sword_shoot(Weapon weapon, vec3f position, vec3f direction)
{
    f32 t = atan(direction.z / direction.x);
    Projectile* proj = projectile_create(SWORD, TRUE);
    proj->speed = 10;
    proj->position = position;
    proj->rotation = t + (direction.x > 0 ? 0 : PI);
    proj->direction = direction;
    proj->position.y = 0.5f;
}