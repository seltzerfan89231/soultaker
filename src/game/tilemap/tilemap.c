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
    // returns true if projectile collides with a wall
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
        }
    }
    return FALSE;
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