#include "projectile.h"
#include <stdlib.h>

ProjectileArray projectiles;

Projectile* projectile_create(u8 friendly)
{
    Projectile* projectile = malloc(sizeof(Projectile));
    projectile->scale = 1;
    projectile->speed = 10;
    projectile->lifetime = 1;
    projectile->rotation = 0;
    projectile->tex = BULLET_TEX;
    projectile->direction = vec3f_create(0, 0, 0);
    projectile->friendly = friendly;
    projectile->hitbox_radius = 0.3;
    projectile->timer = 0;
    projectile_array_push(&projectiles, projectile);
    return projectile;
}

void projectile_update(Projectile* projectile, f32 dt)
{
    projectile->position = vec3f_add(projectile->position, vec3f_scale(projectile->speed * dt, projectile->direction));
    if (projectile->timer >= 0.03) {
        Parjicle *parjicle = parjicle_create(projectile->rotation);
        parjicle->position = projectile->position;
        parjicle->scale = 0.15f;
        parjicle->direction = projectile->direction;
        parjicle->speed = 0.1;
        parjicle->lifetime = 0.3;
        parjicle->color.r = (float)rand() / RAND_MAX;
        parjicle->color.g = (float)rand() / RAND_MAX;
        parjicle->color.b = (float)rand() / RAND_MAX;
        projectile->timer = 0;
    }
    projectile->lifetime -= dt;
    projectile->timer += dt;
}

void projectile_destroy(Projectile* projectile)
{
    free(projectile);
}

_ARRAY_DEFINE(Projectile, projectile)