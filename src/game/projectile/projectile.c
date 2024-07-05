#include "projectile.h"
#include <stdlib.h>
#include <glfw.h>

ProjectileArray projectiles;

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
    projectile->timer = -0.1;
    projectile_array_push(&projectiles, projectile);
    return projectile;
}

void projectile_update(Projectile* projectile, f32 dt)
{
    projectile->position = vec3f_add(projectile->position, vec3f_scale(projectile->speed * dt, projectile->direction));
    if (projectile->timer >= 0.03) {
        Particle *particle = particle_create();
        particle->position = projectile->position;
        particle->scale = 0.15f;
        particle->direction = vec3f_scale(-1, projectile->direction);
        particle->speed = 5;
        particle->lifetime = 0.3;
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