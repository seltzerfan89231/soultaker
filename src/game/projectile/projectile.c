#include "projectile.h"
#include <stdlib.h>
#include <stdio.h>

ProjectileArray projectiles;

Projectile* projectile_create(u32 id, u8 friendly)
{
    Projectile* projectile = malloc(sizeof(Projectile));
    projectile->scale = 1;
    projectile->speed = 10;
    projectile->lifetime = 1;
    projectile->rotation = 0;
    projectile->damage = 1;
    projectile->tex = BULLET_TEX;
    projectile->id = id;
    projectile->direction = vec3f_create(0, 0, 0);
    projectile->friendly = friendly;
    projectile->hitbox_radius = 0.3;
    projectile->timer = 0;
    projectile_array_push(&projectiles, projectile);
    return projectile;
}

#define _UPDATE(_id, _lid) \
    case _id : _lid##_update(projectile, dt); break;

void projectile_update(Projectile* projectile, f32 dt)
{
    projectile->position = vec3f_add(projectile->position, vec3f_scale(projectile->speed * dt, projectile->direction));
    switch (projectile->id) {
        _UPDATE(SWORD, sword);
    }
    projectile->lifetime -= dt;
    projectile->timer += dt;
}

void projectile_destroy(Projectile* projectile)
{
    free(projectile);
}

_ARRAY_DEFINE(Projectile, projectile)