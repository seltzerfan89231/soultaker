#ifndef GAME_UTIL_H
#define GAME_UTIL_H

#include "entity/entity.h"
#include "projectile/projectile.h"
#include "particle/particle.h"
#include "obstacle/obstacle.h"
#include "parjicle/parjicle.h"
#include "parstacle/parstacle.h"
#include "tile/tile.h"
#include "wall/wall.h"
#include "player/player.h"
#include "aud/aud.h"
#include "tilemap/tilemap.h"
#include "../util/array.h"

extern ProjectileArray projectiles;
extern EntityArray entities;
extern ParticleArray particles;
extern ParjicleArray parjicles;
extern ParstacleArray parstacles;
extern ObstacleArray obstacles;
extern TileArray tiles;
extern WallArray walls;
extern Player player;
extern TileMap map;

extern f32 game_time;
extern f32 game_dt;
extern bool game_paused;

#endif