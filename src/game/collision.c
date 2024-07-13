#include "game.h"

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
                projectile_array_cut(&projectiles, j);
            }
            else
                j++;
        }
        i++;
    }
}

static void collide_walls_projectiles(void)
{
    i32 i, j;
    i = 0;
    while (i < walls.length) {
        Wall *wall = walls.buffer[i];  
        j = 0;
        while (j < projectiles.length) {
            Projectile *proj = projectiles.buffer[j];
            if (proj->position.x + proj->hitbox_radius > wall->position.x   &&
              proj->position.x - proj->hitbox_radius < wall->position.x + 1 &&
              proj->position.z + proj->hitbox_radius > wall->position.z     &&
              proj->position.z - proj->hitbox_radius < wall->position.z + 1)
                projectile_array_cut(&projectiles, j);
            else
                j++;
        }
        i++;
    }
}

static void collide_obstacles_projectiles()
{
    i32 i, j;
    i = 0;
    while (i < obstacles.length) {
        Obstacle *obstacle = obstacles.buffer[i];
        j = 0;
        while (j < projectiles.length) {
            f32 dx, dz;
            Projectile *proj = projectiles.buffer[j];
            dx = obstacle->position.x - proj->position.x;
            dz = obstacle->position.z - proj->position.z;
            if (vec2f_mag(vec2f_create(dx, dz)) < obstacle->hitbox_radius + proj->hitbox_radius)
                projectile_array_cut(&projectiles, j);
            else
                j++;
        }
        i++;
    }
}

static void collide_obstacles_entities()
{
    i32 i, j;
    i = 0;
    while (i < obstacles.length) {
        Obstacle *obstacle = obstacles.buffer[i];
        j = 0;
        while (j < entities.length) {
            f32 dx, dz;
            vec2f dir;
            Entity *entity = entities.buffer[j];
            dx = entity->position.x - obstacle->position.x;
            dz = entity->position.z - obstacle->position.z;
            dir = vec2f_create(dx, dz);
            if (vec2f_mag(dir) < obstacle->hitbox_radius + entity->hitbox_radius) {
               dir = vec2f_scale(obstacle->hitbox_radius + entity->hitbox_radius, vec2f_normalize(dir));
               entity->position.x = obstacle->position.x + dir.x;
               entity->position.z = obstacle->position.z + dir.y;
            }
            j++;
        }
        i++;
    }
}

static void collide_walls_entities(f32 dt)
{
    i32 i, j;
    i = 0;
    while (i < walls.length) {
        Wall *wall = walls.buffer[i];
        j = 0;
        while (j < entities.length) {
            Entity *entity = entities.buffer[j];
            vec3f prev_position = vec3f_sub(entity->position, vec3f_scale(entity->speed * dt, entity->direction));
            if (entity->position.x + entity->hitbox_radius > wall->position.x
              && entity->position.x - entity->hitbox_radius < wall->position.x + 1
              && entity->position.z + entity->hitbox_radius > wall->position.z
              && entity->position.z - entity->hitbox_radius < wall->position.z + 1) {
                if (prev_position.x < wall->position.x
                  && entity->direction.x > 0
                  && prev_position.z < wall->position.z + 1 + entity->hitbox_radius
                  && prev_position.z > wall->position.z - entity->hitbox_radius) {
                    entity->position.x = wall->position.x - entity->hitbox_radius;
                    entity->direction.x = 0;
                }
                else if (prev_position.x > wall->position.x + 1
                  && entity->direction.x < 0
                  && prev_position.z < wall->position.z + 1 + entity->hitbox_radius
                  && prev_position.z > wall->position.z - entity->hitbox_radius) {
                    entity->position.x = wall->position.x + 1 + entity->hitbox_radius;
                    entity->direction.x = 0;
                }
                else if (prev_position.z < wall->position.z
                  && entity->direction.z > 0
                  && prev_position.x < wall->position.x + 1 + entity->hitbox_radius
                  && prev_position.x > wall->position.x - entity->hitbox_radius) {
                    entity->position.z = wall->position.z - entity->hitbox_radius;
                    entity->direction.z = 0;
                }
                else if (prev_position.z > wall->position.z + 1
                  && entity->direction.z < 0
                  && prev_position.x < wall->position.x + 1 + entity->hitbox_radius
                  && prev_position.x > wall->position.x - entity->hitbox_radius) {
                    entity->position.z = wall->position.z + 1 + entity->hitbox_radius;
                    entity->direction.z = 0;
                }
            }
            j++;
        }
        i++;
    }
}

void collide_objects(f32 dt)
{
    collide_walls_entities(dt);
    collide_walls_projectiles();
    collide_obstacles_projectiles();
    collide_obstacles_entities();
    collide_entities_projectiles();
}