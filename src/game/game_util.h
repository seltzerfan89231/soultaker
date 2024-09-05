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
#include "sentry/sentry.h"
#include "aoe/aoe.h"
#include "../util/array.h"

extern ProjectileArray global_projectiles;
extern EntityArray global_entities;
extern ParticleArray global_particles;
extern ParjicleArray global_parjicles;
extern ParstacleArray global_parstacles;
extern ObstacleArray global_obstacles;
extern TileArray global_tiles;
extern TileArray interactable_tiles;
extern WallArray global_walls;
extern AOEArray global_aoes;
extern SentryArray global_sentries;
extern Player player;
extern TileMap map;

extern f32 game_time;
extern f32 game_dt;
extern bool game_paused;

#endif