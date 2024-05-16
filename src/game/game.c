#include "game.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <glfw.h>

Game game;
Entity* player;

void game_init(void)
{
    game.projectiles = (ProjectileStorage) {
        .vertex_buffer = malloc(1000000 * sizeof(Entity*)),
        .obj_buffer = malloc(1000000 * sizeof(f32)),
        .length = 0
    };

    game.entities = (EntityStorage) {
        .vertex_buffer = malloc(1000000 * sizeof(Entity*)),
        .obj_buffer = malloc(1000000 * sizeof(f32)),
        .length = 0
    };

    game.tiles = (TileStorage) {
        .vertex_buffer = malloc(1000000 * sizeof(Tile*)),
        .obj_buffer = malloc(1000000 * sizeof(f32)),
        .length = 0
    };

    game.walls = (WallStorage) {
        .vertex_buffer = malloc(1000000 * sizeof(Tile*)),
        .obj_buffer = malloc(1000000 * sizeof(f32)),
        .length = 0
    };
}

void game_setup(void)
{
    for (f32 i = 0; i < 30; i++) {
        for (f32 j = 0; j < 30; j++) {
            if (i == 0 || j == 0 || j == 29 || i == 29) {
                Wall *wall;
                wall = wall_create(WALL2);
                wall->position = vec3i_create(i - 15, 3, j - 15);
                wall_push_data(wall, game.walls.vertex_buffer, game.walls.length);
                game.walls.obj_buffer[game.walls.length++] = wall;
            }
            else {
                Tile *tile;
                tile = tile_create(FLOOR);
                tile->position = vec2i_create(i - 15, j - 15);
                tile_push_data(tile, game.tiles.vertex_buffer, game.tiles.length);
                game.tiles.obj_buffer[game.tiles.length++] = tile;
            }
        }
    }

    player = entity_create(PLAYER);
    player->position = vec3f_create(0.0f, 0.0f, 0.0f);
    entity_push_data(player, game.entities.vertex_buffer, game.entities.length);
    game.entities.obj_buffer[game.entities.length++] = player;

    Entity* entity = entity_create(ENEMY);
    entity->position = vec3f_create(5, 0, 0);
    entity_push_data(player, game.entities.vertex_buffer, game.entities.length);
    game.entities.obj_buffer[game.entities.length++] = entity;
}

void game_update(f32 dt)
{
    static f32 cooldown;
    if (glfwGetTime() - cooldown >= 0.5) {
        cooldown = glfwGetTime();
        Projectile* proj = projectile_create(ONE);
        proj->position = game.entities.obj_buffer[1]->position;
        proj->rotation = 1.1;
        proj->direction = vec3f_create(cos(proj->rotation), 0.0f, sin(proj->rotation));
        proj->position.y = 0.5f;
        proj->speed = 4;
        proj->tex = vec2f_create(0.5, 0);
        game.projectiles.obj_buffer[game.projectiles.length++] = proj;
        projectile_push_data(proj, game.projectiles.vertex_buffer, game.projectiles.length);
    }
    for (i32 i = 0; i < game.entities.length; i++) {
        Entity *entity = game.entities.obj_buffer[i];
        entity_update_position(entity, dt);
        entity_push_data(entity, game.entities.vertex_buffer, i);
    }
    for (i32 i = 0; i < game.projectiles.length; i++) {
        Projectile *proj = game.projectiles.obj_buffer[i];
        projectile_update_position(proj, dt);
        projectile_push_data(proj, game.projectiles.vertex_buffer, i);
    }
}

void game_set_target(vec3f target)
{
    player->position = target;
}

void game_destroy(void)
{
    tile_storage_destroy(game.tiles);
    entity_storage_destroy(game.entities);
    projectile_storage_destroy(game.projectiles);
}

void game_shoot(vec2f pos, f32 rotation, f32 tilt, f32 zoom, f32 ar)
{
    static f32 cooldown;
    if (glfwGetTime() - cooldown < 0.5)
        return;
    cooldown = glfwGetTime();
    assert(player != NULL);
    Projectile* proj = projectile_create(ONE);
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
    game.projectiles.obj_buffer[game.projectiles.length++] = proj;
    projectile_push_data(proj, game.projectiles.vertex_buffer, game.projectiles.length);
}
