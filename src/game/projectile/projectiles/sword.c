#include "../projectile.h"

void sword_update(Projectile *projectile, f32 dt)
{
    if (projectile->timer >= 0.03) {
        Parjicle *parjicle = parjicle_create(projectile->rotation);
        parjicle->position = projectile->position;
        parjicle->scale = 0.1f;
        parjicle->direction = projectile->direction;
        parjicle->speed = 0.1;
        parjicle->lifetime = 0.3;
        parjicle->color.r = (float)rand() / RAND_MAX;
        parjicle->color.g = (float)rand() / RAND_MAX;
        parjicle->color.b = (float)rand() / RAND_MAX;
        projectile->timer = 0;
    }
}