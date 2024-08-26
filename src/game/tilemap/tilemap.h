#ifndef TILEMAP_H
#define TILEMAP_H

#include "../tile/tile.h"
#include "../wall/wall.h"
#include "../../util/type.h"
#include "../projectile/projectile.h"
#include "../entity/entity.h"
#include "../obstacle/obstacle.h"

#define TILEMAP_TILE 0
#define TILEMAP_WALL 1

typedef struct {
    Tile *tile;
    Wall *wall;
    ObstacleArray obstacles;
} TileMapInfo;

typedef struct {
    TileMapInfo *buffer;
    u32 width, length;
} TileMap;

extern TileMap tilemap;

void tilemap_init(void);
void tilemap_insert_tile(Tile *tile);
void tilemap_insert_wall(Wall *wall);
void tilemap_insert_obstacle(Obstacle *obstacle);
Tile* tilemap_get_tile(u32 x, u32 z);
Wall* tilemap_get_wall(u32 x, u32 z);
bool tilemap_collide_projectile(Projectile *proj);
void tilemap_collide_entity(Entity *entity, vec3f prev_position);
void tilemap_reset(u32 width, u32 length);
void tilemap_destroy(void);

#endif