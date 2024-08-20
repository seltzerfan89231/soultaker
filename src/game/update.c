#include "game.h"
#include <omp.h>
#include <time.h>
#include <stdio.h>
#include <assert.h>

static void collide_entities_projectiles(void)
{
    i32 i, j;
    i = 0;
    while (i < entities.length) {
        Entity *entity = entities.buffer[i];
        j = 0;
        while (j < projectiles.length) {
            f32 dx, dz;
            Projectile *proj = projectiles.buffer[j];
            dx = entity->position.x - proj->position.x;
            dz = entity->position.z - proj->position.z;
            if (entity->friendly != proj->friendly && vec2f_mag(vec2f_create(dx, dz)) < entity->hitbox_radius + proj->hitbox_radius) {
                entity_damage(entity, proj->damage);
                projectile_destroy(proj, j);
                if (entity->health <= 0) {
                    entity_destroy(entity, i), i--;
                    break;
                }
            }
            else
                j++;
        }
        i++;
    }
}

static void collide_walls_projectiles(void)
{
    i32 i = 0;
    while (i < projectiles.length) {
        Projectile *proj = projectiles.buffer[i];
        if (tilemap_collide_projectile(proj))
            projectile_destroy(proj, i);
        else
            i++;
    }
}

static void collide_walls_entities(f32 dt)
{
    for (i32 i = 0; i < entities.length; i++) {
        Entity *entity = entities.buffer[i];
        vec3f prev_position = vec3f_sub(entity->position, vec3f_scale(entity->speed * dt, entity->direction));
        tilemap_collide_entity(entity, prev_position);
    }
}

void collide_objects(f32 dt)
{
    collide_walls_entities(dt);
    collide_walls_projectiles();
    collide_entities_projectiles();
}

static void update_entities(f32 dt)
{
    for (i32 i = 0; i < entities.length; i++) {
        Entity *entity = entities.buffer[i];
        entity_update(entity, dt);
        if (entity->health <= 0) {
            entity_destroy(entity, i), i--;
            continue;
        }
        if (entity->position.x < 0)
            entity->position.x = 0;
        if (entity->position.z < 0)
            entity->position.z = 0;
        if (entity->position.x > MAP_WIDTH)
            entity->position.x = MAP_WIDTH;
        if (entity->position.z > MAP_WIDTH)
            entity->position.z = MAP_WIDTH;
    }
}

static void update_projectiles(f32 dt)
{
    for (i32 i = 0; i < projectiles.length; i++) {
        Projectile *proj = projectiles.buffer[i];
        projectile_update(proj, dt);
        if (proj->lifetime <= 0)
            projectile_destroy(proj, i), i--;
    }
}

static void update_particles(f32 dt)
{
    for (i32 i = 0; i < particles.length; i++) {
        Particle *particle = particles.buffer[i];
        particle_update(particle, dt);
        if (particle->lifetime <= 0)
            particle_destroy(particle, i), i--;
    }
}

static void update_parjicles(f32 dt)
{
    for (i32 i = 0; i < parjicles.length; i++) {
        Parjicle *parjicle = parjicles.buffer[i];
        parjicle_update(parjicle, dt);
        if (parjicle->lifetime <= 0)
            parjicle_destroy(parjicle, i), i--;
    }
}

static void update_players(f32 dt)
{
    player_update(&player, dt);
}

void update_objects(f32 dt)
{
    update_entities(dt);
    update_projectiles(dt);
    update_particles(dt);
    update_parjicles(dt);
    update_players(dt);
}