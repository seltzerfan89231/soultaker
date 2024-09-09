#include "../projectile.h"

void shaitan_firestorm_proj_update(Projectile *projectile, f32 dt)
{
    projectile->rotation -= 20 * dt;
}