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
    if (glfwGetTime() - cooldown >= 0.5) {
        cooldown = glfwGetTime();
        Projectile* proj = projectile_create(ONE, 0);
        proj->position = game.entities.buffer[1]->position;
        proj->rotation = 1.1;
        proj->direction = vec3f_create(cos(proj->rotation), 0.0f, sin(proj->rotation));
        proj->position.y = 0.5f;
        proj->speed = 4;
        proj->tex = vec2f_create(0.5, 0);
        projectile_array_push(&game.projectiles, proj);
    }
}

static void update_objects(f32 dt)
{
    for (i32 i = 0; i < game.entities.length; i++) {
        Entity *entity = game.entities.buffer[i];
        entity_update_position(entity, dt);
    }
    for (i32 i = 0; i < game.projectiles.length; i++) {
        Projectile *proj = game.projectiles.buffer[i];
        projectile_update_position(proj, dt);
    }
}

static void collide_objects(void)
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
            if (entity->friendly ^ proj->friendly && vec2f_mag(vec2f_create(dx, dz)) < entity->hitbox_radius + proj->hitbox_radius)
                projectile_array_pop(&game.projectiles, j);
            else
                j++;
        }
        i++;
    }
    
    i = 0;
    while (i < game.walls.length) {
        Wall *wall = game.walls.buffer[i];  
        j = 0;
        while (j < game.projectiles.length) {
            Projectile *proj = game.projectiles.buffer[j];
            if (proj->position.x + proj->hitbox_radius > wall->position.x   &&
              proj->position.x - proj->hitbox_radius < wall->position.x + 1 &&
              proj->position.z + proj->hitbox_radius > wall->position.y     &&
              proj->position.z - proj->hitbox_radius < wall->position.y + 1)
                projectile_array_pop(&game.projectiles, j);
            else
                j++;
        }
        i++;
    }

    i = 0;
    while (i < game.entities.length) {
        j = 0;
        while (j < game.walls.length) {
            j++;
        }
        i++;
    }
}

void game_init(void)
{
    game.projectiles = projectile_array_create(1000000);
    game.entities = entity_array_create(1000000);
    game.tiles = tile_array_create(1000000);
    game.walls = wall_array_create(1000000);
}

void game_setup(void)
{
    for (f32 i = 0; i < MAP_SIZE; i++) {
        for (f32 j = 0; j < MAP_SIZE; j++) {
            if (i == 0 || j == 0 || j == MAP_SIZE - 1 || i == MAP_SIZE - 1) {
                Wall *wall;
                wall = wall_create(WALL2);
                wall->position = vec2i_create(i - MAP_SIZE / 2, j - MAP_SIZE / 2);
                wall->height = ((int)(i + j)) % 2 == 0 ? 3.0f : 0.8f;
                wall_array_push(&game.walls, wall);
            }
            else {
                Tile *tile;
                tile = tile_create(FLOOR);
                tile->position = vec2i_create(i - MAP_SIZE / 2, j - MAP_SIZE / 2);
                tile_array_push(&game.tiles, tile);
            }
        }
    }

    player = entity_create(PLAYER, 1);
    player->position = vec3f_create(0.0f, 0.0f, 0.0f);
    entity_array_push(&game.entities, player);

    Entity* entity = entity_create(ENEMY, 0);
    entity->position = vec3f_create(5, 0, 0);
    entity_array_push(&game.entities, entity);
}

void game_update(f32 dt)
{
    create_objects();
    update_objects(dt);
    collide_objects();
}

void game_set_direction(vec3f direction)
{
    player->direction = direction;
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
}

void game_shoot(vec2f pos, f32 rotation, f32 tilt, f32 zoom, f32 ar)
{
    static f32 cooldown;
    if (glfwGetTime() - cooldown < 0.5)
        return;
    cooldown = glfwGetTime();
    assert(player != NULL);
    Projectile* proj = projectile_create(ONE, 1);
    proj->speed = 4;
    vec2f dir = vec2f_normalize(vec2f_create((pos.x - 0.5) * ar, pos.y - 0.5 + 1.0 / 4 / zoom));
    f32 dirx, dirz, a, b, c;
    a = atan(-dir.y/dir.x);
    b = PI/2 + tilt;
    c = tan(a) * tan(a) / cos(b) / cos(b) + 1;
    dir.x =  dir.x > 0 ? 1 / sqrt(c) : -1 / sqrt(c);
    dir.y = -dir.y > 0 ? sqrt(1 - 1 / c) : -sqrt(1 - 1 / c);
    dirx = dir.x * cos(rotation - HALFPI) - dir.y * sin(rotation - HALFPI);
    dirz = dir.x * sin(rotation - HALFPI) + dir.y * cos(rotation - HALFPI);
    proj->position = player->position;
    f32 t = atan(dirz / dirx);
    proj->rotation = t + (dirx > 0 ? 0 : PI);
    proj->direction = vec3f_normalize(vec3f_create(dirx, 0.0, dirz));
    proj->position.y = 0.5f;
    proj->tex = vec2f_create(0.5, 0);
    projectile_array_push(&game.projectiles, proj);
}
