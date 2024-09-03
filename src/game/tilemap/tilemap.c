#include "tilemap.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

TileMap tilemap;

static bool in_tilemap(i32 x, i32 z)
{
    return x >= 0 && x < tilemap.width && z >= 0 && z < tilemap.length;
}

static i32 idx_at(i32 x, i32 z)
{
    if (!in_tilemap(x, z))
        return -1;
    return x * tilemap.length + z;
}

static i32 max(i32 a, i32 b)
{
    if (a > b)
        return a;
    return b;
}

void tilemap_init(void)
{
    tilemap.buffer = NULL;
    tilemap.width = 0;
    tilemap.length = 0;
}

void tilemap_insert_tile(Tile *tile)
{
    i32 idx = idx_at(tile->position.x, tile->position.z);
    if (idx != -1)
        tilemap.buffer[idx].tile = tile;
}

void tilemap_insert_wall(Wall *wall)
{
    f32 x, z, w, l;
    i32 x1, x2, z1, z2;
    x = wall->position.x, z = wall->position.z;
    w = wall->dimensions.w, l = wall->dimensions.l;
    x1 = (int) x, x2 = (int) (x + w - 0.00001);
    z1 = (int) z, z2 = (int) (z + l - 0.00001);
    for (i32 i = max(x1, 0); i <= x2 && i < tilemap.width; i++)
        for (i32 j = max(z1, 0); j <= z2 && j < tilemap.length; j++)
            tilemap.buffer[idx_at(i, j)].wall = wall;
}

void tilemap_insert_obstacle(Obstacle *obstacle)
{
    f32 x, z, r;
    i32 x1, x2, z1, z2;
    x = obstacle->position.x, z = obstacle->position.z;
    r = obstacle->hitbox_radius;
    x1 = (int) (x - r), x2 = (int) (x + r);
    z1 = (int) (z - r), z2 = (int) (z + r);
    for (i32 i = max(x1, 0); i <= x2 && i < tilemap.width; i++)
        for (i32 j = max(z1, 0); j <= z2 && j < tilemap.length; j++)
            obstacle_array_push(&tilemap.buffer[idx_at(i, j)].obstacles, obstacle);
}

Tile* tilemap_get_tile(u32 x, u32 z)
{
    i32 idx = idx_at(x, z);
    if (idx == -1)
        return NULL;
    return tilemap.buffer[idx].tile;
}

Wall* tilemap_get_wall(u32 x, u32 z)
{
    i32 idx = idx_at(x, z);
    if (idx == -1)
        return NULL;
    return tilemap.buffer[idx].wall;
}

Obstacle** tilemap_get_obstacles(u32 x, u32 z)
{
    i32 idx = idx_at(x, z);
    if (idx == -1)
        return NULL;
    TileMapInfo t = tilemap.buffer[idx];
    Obstacle **arr = malloc((t.obstacles.length + 1) * sizeof(Obstacle*));
    if (arr == NULL) {
        printf("something went wrong");
        exit(1);
    }
    memcpy(arr, t.obstacles.buffer, t.obstacles.length * sizeof(Obstacle*));
    arr[t.obstacles.length] = NULL;
    return arr;
}

static bool collide_projectile(Projectile *proj, i32 x, i32 y)
{
    if (tilemap_get_wall(x, y) != NULL)
        return TRUE;
    Obstacle **arr = tilemap_get_obstacles(x, y);
    if (arr == NULL)
        return FALSE;
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
    return FALSE;
}

bool tilemap_collide_projectile(Projectile *proj)
{
    f32 x, z, r;
    i32 x1, x2, z1, z2;
    x = proj->position.x, z = proj->position.z;
    r = proj->hitbox_radius;
    x1 = (int) (x - r), x2 = (int) (x + r);
    z1 = (int) (z - r), z2 = (int) (z + r);
    for (i32 i = x1; i <= x2; i++)
        for (i32 j = z1; j <= z2; j++)
            if (collide_projectile(proj, i, j))
                return TRUE;
    return FALSE;
}

static void move_along_wall(Wall *wall, Entity *entity, vec3f prev_position)
{
    bool condition = entity->position.x + entity->hitbox_radius > wall->position.x
        && entity->position.x - entity->hitbox_radius < wall->position.x + wall->dimensions.w
        && entity->position.z + entity->hitbox_radius > wall->position.z
        && entity->position.z - entity->hitbox_radius < wall->position.z + wall->dimensions.l;
    
    if (!condition)
        return;

    if (prev_position.x < wall->position.x
        && entity->direction.x > 0
        && prev_position.z < wall->position.z + wall->dimensions.l + entity->hitbox_radius
        && prev_position.z > wall->position.z - entity->hitbox_radius) {
            entity->position.x = wall->position.x - entity->hitbox_radius;
            entity->direction.x = 0;
    }
    else if (prev_position.x > wall->position.x + wall->dimensions.w
        && entity->direction.x < 0
        && prev_position.z < wall->position.z + wall->dimensions.l + entity->hitbox_radius
        && prev_position.z > wall->position.z - entity->hitbox_radius) {
            entity->position.x = wall->position.x + wall->dimensions.w + entity->hitbox_radius;
            entity->direction.x = 0;
    }
    else if (prev_position.z < wall->position.z
        && entity->direction.z > 0
        && prev_position.x < wall->position.x + wall->dimensions.w + entity->hitbox_radius
        && prev_position.x > wall->position.x - entity->hitbox_radius) {
            entity->position.z = wall->position.z - entity->hitbox_radius;
            entity->direction.z = 0;
    }
    else if (prev_position.z > wall->position.z + wall->dimensions.l
        && entity->direction.z < 0
        && prev_position.x < wall->position.x + wall->dimensions.w + entity->hitbox_radius
        && prev_position.x > wall->position.x - entity->hitbox_radius) {
            entity->position.z = wall->position.z + wall->dimensions.l + entity->hitbox_radius;
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

static void collide_entity(Entity *entity, vec3f prev_position, i32 x, i32 z)
{
    Wall *wall = tilemap_get_wall(x, z);
    if (wall != NULL)
        move_along_wall(wall, entity, prev_position);
    Obstacle **arr = tilemap_get_obstacles(x, z);
    if (arr == NULL)
        return;
    for (i32 k = 0; arr[k] != NULL; k++) {
        Obstacle *obstacle = arr[k];
        move_along_obstacle(obstacle, entity);
    }
    free(arr);
}

void tilemap_collide_entity(Entity *entity, vec3f prev_position)
{
    f32 x, z, r;
    i32 x1, x2, z1, z2;
    x = entity->position.x, z = entity->position.z;
    r = entity->hitbox_radius;
    x1 = (int) (x - r), x2 = (int) (x + r);
    z1 = (int) (z - r), z2 = (int) (z + r);
    Tile *tile = tilemap_get_tile(x, z);
    if (tile != NULL)
        tile_interact(tile, entity);
    for (i32 i = x1; i <= x2; i++)
        for (i32 j = z1; j <= z2; j++)
            collide_entity(entity, prev_position, i, j);
    if (entity->position.x < 0)
        entity->position.x = 0;
    if (entity->position.z < 0)
        entity->position.z = 0;
    if (entity->position.x > tilemap.width)
        entity->position.x = tilemap.width;
    if (entity->position.z > tilemap.length)
        entity->position.z = tilemap.length;
}

void tilemap_reset(u32 width, u32 length)
{
    for (i32 i = 0; i < tilemap.width * tilemap.length; i++)
        obstacle_array_destroy(&tilemap.buffer[i].obstacles);
    free(tilemap.buffer);
    tilemap.width = width;
    tilemap.length = length;
    tilemap.buffer = malloc(width * length * sizeof(TileMapInfo));
    for (i32 i = 0; i < width * length; i++) {
        tilemap.buffer[i].tile = NULL;
        tilemap.buffer[i].wall = NULL;
        tilemap.buffer[i].obstacles = obstacle_array_create(0, 1);
    }
}

void tilemap_destroy(void)
{
    free(tilemap.buffer);
}