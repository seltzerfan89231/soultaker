#include "game.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <glfw.h>

Game game;
Entity* player;

static void create_objects(void)
{
    static f32 cooldown;
    if (glfwGetTime() - cooldown >= 0.05) {
        cooldown = glfwGetTime();
        for (i32 i = 0; i < 1; i++) {
            Projectile* proj = projectile_create(ONE, 0);
            proj->position = game.entities.buffer[1]->position;
            proj->rotation = i * 0.8 + sin(glfwGetTime());
            proj->direction = vec3f_create(cos(proj->rotation), 0.0f, sin(proj->rotation));
            proj->scale = 1.0f;
            proj->lifetime = 3.0f;
            proj->hitbox_radius = (proj->scale - 0.4) / 2;
            proj->position.y = 0.5f;
            projectile_array_push(&game.projectiles, proj);
        }
    }
    static f32 cooldown1;
    if (glfwGetTime() - cooldown1 >= 0.3) {
        cooldown1 = glfwGetTime();
        for (i32 i = 0; i < 6; i++) {
            if (i % 2) {
                Particle *particle = particle_create();
                particle->position = vec3f_create(12.0f, 0.5f, 15.0f);
                particle->direction = vec3f_create(cos(i), 0.0f, sin(i));
                particle->speed = 2.0f;
                particle_array_push(&game.particles, particle);
            } else {
                Parjicle *parjicle = parjicle_create(i);
                parjicle->position = vec3f_create(12.0f, 0.5f, 15.0f);
                parjicle->direction = vec3f_create(cos(i), 0.0f, sin(i));
                parjicle->scale = 0.3f;
                parjicle->speed = 2.0f;
                parjicle_array_push(&game.parjicles, parjicle);
            }
        }
    }
}

static void update_objects(f32 dt)
{
    for (i32 i = 0; i < game.entities.length; i++) {
        Entity *entity = game.entities.buffer[i];
        entity_update(entity, dt);
    }
    for (i32 i = 0; i < game.projectiles.length; i++) {
        Projectile *proj = game.projectiles.buffer[i];
        projectile_update_position(proj, dt);
        if (proj->lifetime <= 0)
            projectile_array_cut(&game.projectiles, i), i--;
    }
    for (i32 i = 0; i < game.particles.length; i++) {
        Particle *particle = game.particles.buffer[i];
        particle_update_position(particle, dt);
        if (particle->lifetime <= 0)
            particle_array_cut(&game.particles, i), i--;
    }
    for (i32 i = 0; i < game.parjicles.length; i++) {
        Parjicle *parjicle = game.parjicles.buffer[i];
        parjicle_update_position(parjicle, dt);
        if (parjicle->lifetime <= 0)
            parjicle_array_cut(&game.parjicles, i), i--;
    }
}

#pragma region collision
static void collide_entities_projectiles(void)
{
    i32 i, j;
    i = 0;
    while (i < game.entities.length) {
        Entity *entity = game.entities.buffer[i];
        j = 0;
        while (j < game.projectiles.length) {
            f32 dx, dz;
            Projectile *proj = game.projectiles.buffer[j];
            dx = entity->position.x - proj->position.x;
            dz = entity->position.z - proj->position.z;
            if (entity->friendly != proj->friendly && vec2f_mag(vec2f_create(dx, dz)) < entity->hitbox_radius + proj->hitbox_radius) {
                projectile_array_cut(&game.projectiles, j);
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
    while (i < game.walls.length) {
        Wall *wall = game.walls.buffer[i];  
        j = 0;
        while (j < game.projectiles.length) {
            Projectile *proj = game.projectiles.buffer[j];
            if (proj->position.x + proj->hitbox_radius > wall->position.x   &&
              proj->position.x - proj->hitbox_radius < wall->position.x + 1 &&
              proj->position.z + proj->hitbox_radius > wall->position.z     &&
              proj->position.z - proj->hitbox_radius < wall->position.z + 1)
                projectile_array_cut(&game.projectiles, j);
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
    while (i < game.obstacles.length) {
        Obstacle *obstacle = game.obstacles.buffer[i];
        j = 0;
        while (j < game.projectiles.length) {
            f32 dx, dz;
            Projectile *proj = game.projectiles.buffer[j];
            dx = obstacle->position.x - proj->position.x;
            dz = obstacle->position.z - proj->position.z;
            if (vec2f_mag(vec2f_create(dx, dz)) < obstacle->hitbox_radius + proj->hitbox_radius)
                projectile_array_cut(&game.projectiles, j);
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
    while (i < game.obstacles.length) {
        Obstacle *obstacle = game.obstacles.buffer[i];
        j = 0;
        while (j < game.entities.length) {
            f32 dx, dz;
            vec2f dir;
            Entity *entity = game.entities.buffer[j];
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
    while (i < game.walls.length) {
        Wall *wall = game.walls.buffer[i];
        j = 0;
        while (j < game.entities.length) {
            Entity *entity = game.entities.buffer[j];
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
    game.projectiles = projectile_array_create(10000);
    game.entities = entity_array_create(10000);
    game.particles = particle_array_create(10000);
    game.parjicles = parjicle_array_create(10000);
    game.parstacles = parstacle_array_create(10000);
    game.obstacles = obstacle_array_create(10000);
    game.tiles = tile_array_create(10000);
    game.walls = wall_array_create(10000);
}

void game_setup(void)
{
    for (i32 i = 0; i < MAP_WIDTH; i++)
        for (i32 j = 0; j < MAP_WIDTH; j++)
            if (i == 0 || j == 0 || j == MAP_WIDTH - 1 || i == MAP_WIDTH - 1 || (i == 12 && j == 12))
                wall_array_push(&game.walls, wall_create(WALL2, i, j, ((int)(i + j)) % 2 == 0 ? 3.0f : 0.8f));
            else
                tile_array_push(&game.tiles, tile_create(FLOOR, i, j));

    player = entity_create(KNIGHT, 1);
    player->position = vec3f_create(15.0f, 0.0f, 15.0f);
    entity_array_push(&game.entities, player);

    Entity* entity = entity_create(KNIGHT, 0);
    entity->position = vec3f_create(20, 0, 15);
    entity->scale = 1.0f;
    entity_array_push(&game.entities, entity);

    Projectile* proj = projectile_create(ONE, 1);
    proj->position = vec3f_create(15.0f, 0.0f, 13.0f);
    proj->speed = 0.5;
    proj->direction = vec3f_create(0.0f, 1.0f, 0.0f);
    proj->rotation = 0.0f;
    projectile_array_push(&game.projectiles, proj);

    Obstacle *obstacle = obstacle_create();
    obstacle->position = vec3f_create(10.0f, 0.0f, 10.0f);
    obstacle->hitbox_radius = 0.3f;
    obstacle->scale = 3.0f;
    obstacle_array_push(&game.obstacles, obstacle);

    Parstacle *parstacle = parstacle_create();
    parstacle->position = vec3f_create(20.0f, 0.0f, 20.0f);
    parstacle->scale = 1.8f;
    parstacle_array_push(&game.parstacles, parstacle);
}

void game_update(f32 dt)
{
    create_objects();
    update_objects(dt);
    collide_objects(dt);
}

void game_set_direction(vec3f direction)
{
    entity_set_direction(player, direction);
}

void game_set_target(vec3f target)
{
    player->position = target;
}

void game_destroy(void)
{
    tile_array_destroy(&game.tiles);
    wall_array_destroy(&game.walls);
    entity_array_destroy(&game.entities);
    projectile_array_destroy(&game.projectiles);
    particle_array_destroy(&game.particles);
    obstacle_array_destroy(&game.obstacles);
    parstacle_array_destroy(&game.parstacles);
    parjicle_array_destroy(&game.parjicles);
}

void game_shoot(vec2f pos, f32 rotation, f32 tilt, f32 zoom, f32 ar)
{
    static f32 cooldown;
    vec2f dir = vec2f_normalize(vec2f_create((pos.x - 0.5) * ar, pos.y - 0.5 + 1.0 / 4 / zoom));
    f32 dirx, dirz, a, b, c;
    a = atan(-dir.y/dir.x);
    b = PI/2 + tilt;
    c = tan(a) * tan(a) / cos(b) / cos(b) + 1;
    dir.x =  dir.x > 0 ? 1 / sqrt(c) : -1 / sqrt(c);
    dir.y = -dir.y > 0 ? sqrt(1 - 1 / c) : -sqrt(1 - 1 / c);
    dirx = dir.x * cos(rotation - HALFPI) - dir.y * sin(rotation - HALFPI);
    dirz = dir.x * sin(rotation - HALFPI) + dir.y * cos(rotation - HALFPI);
    entity_set_state(player, KNIGHT_SHOOT_1);
    player->face_dir = FALSE;
    player->facing = vec2f_normalize(vec2f_create(dirx, dirz));
    if (glfwGetTime() - cooldown < 0.5)
        return;
    cooldown = glfwGetTime();
    assert(player != NULL);
    Projectile* proj = projectile_create(ONE, 1);
    proj->speed = 4;
    proj->position = player->position;
    f32 t = atan(dirz / dirx);
    proj->rotation = t + (dirx > 0 ? 0 : PI);
    proj->direction = vec3f_normalize(vec3f_create(dirx, 0.0, dirz));
    proj->position.y = 0.5f;
    projectile_array_push(&game.projectiles, proj);
}

void game_idle(void)
{
    entity_set_state(player, KNIGHT_IDLE);
}