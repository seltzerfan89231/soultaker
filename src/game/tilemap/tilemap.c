#include "tilemap.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

TileMap tilemap;

static bool in_tilemap(u32 x, u32 z)
{
    return x >= 0 && x < tilemap.width && z >= 0 && z < tilemap.length;
}

void tilemap_init(void)
{
    tilemap.buffer = NULL;
    tilemap.width = 0;
    tilemap.length = 0;
}

void tilemap_insert_tile(Tile *tile)
{
    if (!in_tilemap(tile->position.x, tile->position.z))
        return;
    i32 idx = tile->position.x * tilemap.width + tile->position.z;
    tilemap.buffer[idx].is_wall = FALSE; 
    tilemap.buffer[idx].ptr = tile;
}

void tilemap_insert_wall(Wall *wall)
{
    if (!in_tilemap(wall->position.x, wall->position.z))
        return;
    i32 idx = wall->position.x * tilemap.width + wall->position.z;
    tilemap.buffer[idx].is_wall = TRUE; 
    tilemap.buffer[idx].ptr = wall;
}

void tilemap_insert_obstacle(Obstacle *obstacle)
{
    f32 x, z, r;
    i32 x1, x2, z1, z2;
    x = obstacle->position.x, z = obstacle->position.z;
    r = obstacle->hitbox_radius;
    x1 = (int) (x - r), x2 = (int) (x + r);
    z1 = (int) (z - r), z2 = (int) (z + r);
    for (i32 i = x1; i <= x2 && i < tilemap.width; i++) {
        if (i < 0)
            continue;
        for (i32 j = z1; j <= z2 && j < tilemap.length; j++) {
            if (j < 0)
                continue;
            obstacle_array_push(&tilemap.buffer[i * tilemap.width + j].obstacles, obstacle);
        }
    }
}

Tile* tilemap_get_tile(u32 x, u32 z)
{
    if (!in_tilemap(x, z))
        return NULL;
    TileMapPtr t = tilemap.buffer[x * tilemap.width + z];
    if (t.ptr == NULL || t.is_wall)
        return NULL;
    return (Tile*)t.ptr;
}

Wall* tilemap_get_wall(u32 x, u32 z)
{
    if (!in_tilemap(x, z))
        return NULL;
    TileMapPtr t = tilemap.buffer[x * tilemap.width + z];
    if (t.ptr == NULL || !t.is_wall)
        return NULL;
    return (Wall*)t.ptr;
}

Obstacle** tilemap_get_obstacles(u32 x, u32 z)
{
    if (!in_tilemap(x, z))
        return NULL;
    TileMapPtr t = tilemap.buffer[x * tilemap.width + z];
    Obstacle **arr = malloc((t.obstacles.length + 1) * sizeof(Obstacle*));
    if (arr == NULL) {
        printf("something went wrong");
        exit(1);
    }
    memcpy(arr, t.obstacles.buffer, t.obstacles.length * sizeof(Obstacle*));
    arr[t.obstacles.length] = NULL;
    return arr;
}

bool tilemap_collide_projectile(Projectile *proj)
{
    f32 x, z, r;
    i32 x1, x2, z1, z2;
    x = proj->position.x, z = proj->position.z;
    r = proj->hitbox_radius;
    x1 = (int) (x - r), x2 = (int) (x + r);
    z1 = (int) (z - r), z2 = (int) (z + r);
    for (i32 i = x1; i <= x2; i++) {
        for (i32 j = z1; j <= z2; j++) {
            if (tilemap_get_wall(i, j) != NULL)
                return TRUE;
            Obstacle **arr = tilemap_get_obstacles(i, j);
            if (arr == NULL)
                continue;
            i32 k = 0;
            while (arr[k] != NULL) {
                Obstacle *obstacle = arr[k];
                f32 dx, dz;
                dx = obstacle->position.x - proj->position.x;
                dz = obstacle->position.z - proj->position.z;
                if (vec2f_mag(vec2f_create(dx, dz)) < obstacle->hitbox_radius + proj->hitbox_radius) {
                    free(arr);
                    return TRUE;
                }
                k++;
            }
            free(arr);
        }
    }
        
    return FALSE;
}

static void move_along_wall(Wall *wall, Entity *entity, vec3f prev_position)
{
    bool condition = entity->position.x + entity->hitbox_radius > wall->position.x
        && entity->position.x - entity->hitbox_radius < wall->position.x + 1
        && entity->position.z + entity->hitbox_radius > wall->position.z
        && entity->position.z - entity->hitbox_radius < wall->position.z + 1;
    
    if (!condition)
        return;

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

static void move_along_obstacle(Obstacle *obstacle, Entity *entity)
{
    f32 dx, dz;
    vec2f dir;
    dx = entity->position.x - obstacle->position.x;
    dz = entity->position.z - obstacle->position.z;
    dir = vec2f_create(dx, dz);
    if (vec2f_mag(dir) < obstacle->hitbox_radius + entity->hitbox_radius) {
        dir = vec2f_scale(obstacle->hitbox_radius + entity->hitbox_radius, vec2f_normalize(dir));
        entity->position.x = obstacle->position.x + dir.x;
        entity->position.z = obstacle->position.z + dir.y;
    }
}

void tilemap_collide_entity(Entity *entity, vec3f prev_position)
{
    f32 x, z, r;
    i32 x1, x2, z1, z2;
    x = entity->position.x, z = entity->position.z;
    r = entity->hitbox_radius;
    x1 = (int) (x - r), x2 = (int) (x + r);
    z1 = (int) (z - r), z2 = (int) (z + r);
    for (i32 i = x1; i <= x2; i++) {
        for (i32 j = z1; j <= z2; j++) {
            Wall *wall = tilemap_get_wall(i, j);
            if (wall != NULL)
                move_along_wall(wall, entity, prev_position);
            Obstacle **arr = tilemap_get_obstacles(i, j);
            if (arr == NULL)
                continue;
            for (i32 k = 0; arr[k] != NULL; k++) {
                Obstacle *obstacle = arr[k];
                move_along_obstacle(obstacle, entity);
            }
            free(arr);
        }
    }
}

void tilemap_reset(u32 width, u32 length)
{
    for (i32 i = 0; i < tilemap.width * tilemap.length; i++)
        obstacle_array_destroy(&tilemap.buffer[i].obstacles);
    free(tilemap.buffer);
    tilemap.width = width;
    tilemap.length = length;
    tilemap.buffer = malloc(width * length * sizeof(TileMapPtr));
    for (i32 i = 0; i < width * length; i++) {
        tilemap.buffer[i].is_wall = FALSE;
        tilemap.buffer[i].ptr = NULL;
        tilemap.buffer[i].obstacles = obstacle_array_create(0, 1);
    }
}

void tilemap_destroy(void)
{
    free(tilemap.buffer);
}