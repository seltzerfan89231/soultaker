#include "game.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

f64 game_time;
u8 game_paused;
extern ProjectileArray projectiles;
extern EntityArray entities;
extern ParticleArray particles;
extern ParjicleArray parjicles;
extern ParstacleArray parstacles;
extern ObstacleArray obstacles;
extern TileArray tiles;
extern WallArray walls;
Player player;

static void update_objects(f32 dt)
{
    for (i32 i = 0; i < entities.length; i++) {
        Entity *entity = entities.buffer[i];
        entity_update(entity, dt);
    }
    for (i32 i = 0; i < projectiles.length; i++) {
        Projectile *proj = projectiles.buffer[i];
        projectile_update(proj, dt);
        if (proj->lifetime <= 0)
            projectile_array_cut(&projectiles, i), i--;
    }
    for (i32 i = 0; i < particles.length; i++) {
        Particle *particle = particles.buffer[i];
        particle_update(particle, dt);
        if (particle->lifetime <= 0)
            particle_array_cut(&particles, i), i--;
    }
    for (i32 i = 0; i < parjicles.length; i++) {
        Parjicle *parjicle = parjicles.buffer[i];
        parjicle_update(parjicle, dt);
        if (parjicle->lifetime <= 0)
            parjicle_array_cut(&parjicles, i), i--;
    }
}

#pragma region collision
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
                projectile_array_cut(&projectiles, j);
                entity->health--;
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

static void collide_objects(f32 dt)
{
    collide_walls_entities(dt);
    collide_walls_projectiles();
    collide_obstacles_projectiles();
    collide_obstacles_entities();
    collide_entities_projectiles();
}
#pragma endregion

void game_init(void)
{
    projectiles = projectile_array_create(0);
    entities = entity_array_create(0);
    particles = particle_array_create(0);
    parjicles = parjicle_array_create(0);
    parstacles = parstacle_array_create(0);
    obstacles = obstacle_array_create(0);
    tiles = tile_array_create(0);
    walls = wall_array_create(0);
    game_time = 0;
    game_paused = FALSE;
}

void game_setup(void)
{
    for (i32 i = 0; i < MAP_WIDTH; i++)
        for (i32 j = 0; j < MAP_WIDTH; j++)
            if (i == 0 || j == 0 || j == MAP_WIDTH - 1 || i == MAP_WIDTH - 1 || (i == 12 && j == 12))
                wall_create(WALL2, i, j, ((int)(i + j)) % 2 == 0 ? 3.0f : 0.8f);
            else
                tile_create(FLOOR, i, j);

    player.entity = entity_create(KNIGHT, 1);
    player.weapon.id = 0;
    player.entity->position = vec3f_create(15.0f, 0.0f, 15.0f);

    Entity* entity = entity_create(ENEMY, 0);
    entity->position = vec3f_create(20, 0, 15);
    entity->scale = 1.0f;

    Obstacle *obstacle = obstacle_create();
    obstacle->position = vec3f_create(10.0f, 0.0f, 10.0f);
    obstacle->hitbox_radius = 0.3f;
    obstacle->scale = 3.0f;

    obstacle = obstacle_create();
    obstacle->position = vec3f_create(12.0f, 0.0f, 10.0f);
    obstacle->hitbox_radius = 0.3f;
    obstacle->scale = 3.0f;

    Parstacle *parstacle = parstacle_create();
    parstacle->position = vec3f_create(20.0f, 0.0f, 20.0f);
    parstacle->scale = 1.8f;
}

void game_update(f32 dt)
{
    if (game_paused)
        return;
    update_objects(dt);
    collide_objects(dt);
    game_time += dt;
}

void game_set_direction(vec3f direction)
{
    entity_set_direction(player.entity, direction);
}

void game_set_target(vec3f target)
{
    player.entity->position = target;
}

void game_destroy(void)
{
    tile_array_destroy(&tiles);
    wall_array_destroy(&walls);
    entity_array_destroy(&entities);
    projectile_array_destroy(&projectiles);
    particle_array_destroy(&particles);
    obstacle_array_destroy(&obstacles);
    parstacle_array_destroy(&parstacles);
    parjicle_array_destroy(&parjicles);
}

void game_shoot(vec2f pos, f32 rotation, f32 tilt, f32 zoom, f32 ar)
{
    vec2f dir = vec2f_normalize(vec2f_create((pos.x - 0.5) * ar, pos.y - 0.5 + 1.0 / 4 / zoom));
    f32 dirx, dirz, a, b, c;
    a = atan(-dir.y/dir.x);
    b = PI/2 + tilt;
    c = tan(a) * tan(a) / cos(b) / cos(b) + 1;
    dir.x =  dir.x > 0 ? 1 / sqrt(c) : -1 / sqrt(c);
    dir.y = -dir.y > 0 ? sqrt(1 - 1 / c) : -sqrt(1 - 1 / c);
    dirx = dir.x * cos(rotation - HALFPI) - dir.y * sin(rotation - HALFPI);
    dirz = dir.x * sin(rotation - HALFPI) + dir.y * cos(rotation - HALFPI);
    assert(player.entity != NULL);
    player.entity->facing = vec2f_normalize(vec2f_create(dirx, dirz));
    player.entity->flag = TRUE;
    player_shoot(&player, vec3f_normalize(vec3f_create(dirx, 0.0, dirz)));
}

vec3f game_get_player_position(void)
{
    return player.entity->position;
}

void game_pause(void)
{
    game_paused = 1 - game_paused;
}

void switch_weapon(void)
{
    player.weapon.id = 1 - player.weapon.id;
}