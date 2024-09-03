#include "game.h"
#include <omp.h>
#include <time.h>
#include <stdio.h>
#include <assert.h>

static void collide_entities_projectiles(void)
{
    i32 i, j;
    i = 0;
    while (i < global_entities.length) {
        Entity *entity = global_entities.buffer[i];
        j = 0;
        while (j < global_projectiles.length) {
            f32 dx, dz;
            Projectile *proj = global_projectiles.buffer[j];
            dx = entity->position.x - proj->position.x;
            dz = entity->position.z - proj->position.z;
            if (entity->friendly != proj->friendly && vec2f_mag(vec2f_create(dx, dz)) < entity->hitbox_radius + proj->hitbox_radius) {
                if (!projectile_hit(proj, entity, j));
                    j++;
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
    while (i < global_projectiles.length) {
        Projectile *proj = global_projectiles.buffer[i];
        if (tilemap_collide_projectile(proj))
            projectile_destroy(proj, i);
        else
            i++;
    }
}

static void collide_walls_entities(f32 dt)
{
    for (i32 i = 0; i < global_entities.length; i++) {
        Entity *entity = global_entities.buffer[i];
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
    for (i32 i = 0; i < global_entities.length; i++) {
        Entity *entity = global_entities.buffer[i];
        entity_update(entity, dt);
        if (entity->health <= 0) {
            entity_destroy(entity, i), i--;
            continue;
        }
    }
}

static void update_projectiles(f32 dt)
{
    for (i32 i = 0; i < global_projectiles.length; i++) {
        Projectile *proj = global_projectiles.buffer[i];
        projectile_update(proj, dt);
        if (proj->lifetime <= 0)
            projectile_destroy(proj, i), i--;
    }
}

static void update_particles(f32 dt)
{
    for (i32 i = 0; i < global_particles.length; i++) {
        Particle *particle = global_particles.buffer[i];
        particle_update(particle, dt);
        if (particle->lifetime <= 0)
            particle_destroy(particle, i), i--;
    }
}

static void update_parjicles(f32 dt)
{
    for (i32 i = 0; i < global_parjicles.length; i++) {
        Parjicle *parjicle = global_parjicles.buffer[i];
        parjicle_update(parjicle, dt);
        if (parjicle->lifetime <= 0)
            parjicle_destroy(parjicle, i), i--;
    }
}

static void update_tiles(f32 dt)
{
    tile_update_timer(dt);
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
    update_tiles(dt);
    update_players(dt);
}