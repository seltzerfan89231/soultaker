#include "../sentry.h"
#include <math.h>

void shaitan_sentry_create(Sentry* sentry)
{

}

void shaitan_sentry_update(Sentry* sentry, f32 dt)
{
    if (sentry->timer < 0) {
        sentry->timer = 2;
        AOE* aoe = aoe_create(sentry->position.x, sentry->position.z, FALSE);
        for (i32 i = 0; i < 8; i++) {
            Projectile* proj = projectile_create(SWORD, FALSE, FALSE);
            f32 theta = 2.0 * PI * i / 8;
            proj->position = sentry->position;
            proj->position.y = 0.5;
            proj->direction.x = cos(theta);
            proj->direction.z = sin(theta);
            proj->rotation = theta;
        }
    }
}