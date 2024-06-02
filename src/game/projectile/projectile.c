#include "projectile.h"
#include <stdlib.h>

Projectile* projectile_create(projtype type, u8 friendly)
{
    Projectile* projectile = malloc(sizeof(Projectile));
    projectile->type = type;
    projectile->scale = 1;
    projectile->speed = 10;
    projectile->lifetime = 1;
    projectile->rotation = 0;
    projectile->direction = vec3f_create(0, 0, 0);
    projectile->friendly = friendly;
    projectile->hitbox_radius = 0.3;
    return projectile;
}

void projectile_update_position(Projectile* projectile, f32 dt)
{
    projectile->position = vec3f_add(projectile->position, vec3f_scale(projectile->speed * dt, projectile->direction));
    projectile->lifetime -= dt;
}

void projectile_destroy(Projectile* projectile)
{
    free(projectile);
}