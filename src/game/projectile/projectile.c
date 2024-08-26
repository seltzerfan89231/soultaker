#include "projectile.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

ProjectileArray global_projectiles;

Projectile* projectile_create(u32 id, bool friendly, bool pierce)
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
    projectile->pierce = pierce;
    projectile->hit_entities = NULL;
    if (pierce) {
        projectile->hit_entities = malloc(sizeof(EntityArray));
        *projectile->hit_entities = entity_array_create(0, 1);
    }
    projectile_array_push(&global_projectiles, projectile);
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

bool projectile_hit(Projectile* projectile, Entity *entity, u32 idx)
{
    if (projectile->pierce) {
        for (i32 i = 0; i < projectile->hit_entities->length; i++)
            if (projectile->hit_entities->buffer[i] == entity)
                return FALSE;
        entity_array_push(projectile->hit_entities, entity);
    }
    entity_damage(entity, projectile->damage);
    if (!projectile->pierce)
        projectile_destroy(projectile, idx);
    return !projectile->pierce;
}

void projectile_destroy(Projectile* projectile, u32 idx)
{
    assert(projectile == global_projectiles.buffer[idx]);
    projectile_array_cut(&global_projectiles, idx);
    entity_array_destroy(projectile->hit_entities);
    free(projectile->hit_entities);
    free(projectile);
}

void destroy_all_projectiles(void)
{
    for (i32 i = 0; i < global_projectiles.length; i++) {
        Projectile *projectile = global_projectiles.buffer[i];
        entity_array_destroy(projectile->hit_entities);
        free(projectile->hit_entities);
        free(projectile);
    }
    projectile_array_destroy(&global_projectiles);
}

_ARRAY_DEFINE(Projectile, projectile)