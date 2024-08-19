#ifndef TILEMAP_H
#define TILEMAP_H

#include "../tile/tile.h"
#include "../wall/wall.h"
#include "../../util/type.h"
#include "../projectile/projectile.h"
#include "../entity/entity.h"

typedef struct {
    bool is_wall;
    void *ptr;
} TileMapPtr;

typedef struct {
    TileMapPtr *buffer;
    u32 width, length;
} TileMap;

extern TileMap tilemap;

void tilemap_init(void);
void tilemap_insert_tile(Tile *tile);
void tilemap_insert_wall(Wall *wall);
Tile* tilemap_get_tile(u32 x, u32 z);
Wall* tilemap_get_wall(u32 x, u32 z);
bool tilemap_collide_projectile(Projectile *proj);
void tilemap_collide_entity(Entity *entity, vec3f prev_position);
void tilemap_reset(u32 width, u32 length);
void tilemap_destroy(void);

#endif