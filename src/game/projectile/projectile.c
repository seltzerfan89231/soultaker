#include "projectile.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

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

void projectile_destroy(Projectile* projectile, u32 idx)
{
    assert(projectile == projectiles.buffer[idx]);
    projectile_array_cut(&projectiles, idx);
    free(projectile);
}

void destroy_all_projectiles(void)
{
    for (i32 i = 0; i < projectiles.length; i++)
        free(projectiles.buffer[i]);
    projectile_array_destroy(&projectiles);
}

_ARRAY_DEFINE(Projectile, projectile)