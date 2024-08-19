#include "tilemap.h"
#include <stdlib.h>
#include <stdio.h>

TileMap tilemap;

void tilemap_init(void)
{
    tilemap.buffer = NULL;
    tilemap.width = 0;
    tilemap.length = 0;
}

void tilemap_insert_tile(Tile *tile)
{
    tilemap.buffer[tile->position.x * tilemap.width + tile->position.z] = 
    (TileMapPtr) {
        .is_wall = FALSE,
        .ptr = tile
    };
}

void tilemap_insert_wall(Wall *wall)
{
    tilemap.buffer[wall->position.x * tilemap.width + wall->position.z] = 
    (TileMapPtr) {
        .is_wall = TRUE,
        .ptr = wall
    };
}

Tile* tilemap_get_tile(u32 x, u32 z)
{
    if (x < 0 || x >= tilemap.width || z < 0 || z >= tilemap.length)
        return NULL;
    TileMapPtr t = tilemap.buffer[x * tilemap.width + z];
    if (t.is_wall)
        return NULL;
    return (Tile*)t.ptr;
}

Wall* tilemap_get_wall(u32 x, u32 z)
{
    if (x < 0 || x >= tilemap.width || z < 0 || z >= tilemap.length)
        return NULL;
    TileMapPtr t = tilemap.buffer[x * tilemap.width + z];
    if (!t.is_wall)
        return NULL;
    return (Wall*)t.ptr;
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
            if (tilemap_get_wall(i, j) != NULL)
                return TRUE;
    return FALSE;
}

static void move_along_wall(Wall *wall, Entity *entity, vec3f prev_position)
{
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
        }
    }
}

void tilemap_reset(u32 width, u32 length)
{
    free(tilemap.buffer);
    tilemap.width = width;
    tilemap.length = length;
    tilemap.buffer = malloc(width * length * sizeof(TileMapPtr));
}

void tilemap_destroy(void)
{
    free(tilemap.buffer);
}