#ifndef GAME_H
#define GAME_H

#include "entity/entity.h"
#include "projectile/projectile.h"
#include "particle/particle.h"
#include "obstacle/obstacle.h"
#include "parjicle/parjicle.h"
#include "parstacle/parstacle.h"
#include "tile/tile.h"
#include "wall/wall.h"
#include "../util/array.h"

#define MAP_WIDTH 50

extern ProjectileArray projectiles;
extern EntityArray entities;
extern ParticleArray particles;
extern ParjicleArray parjicles;
extern ParstacleArray parstacles;
extern ObstacleArray obstacles;
extern TileArray tiles;
extern WallArray walls;

void game_init(void);
void game_setup(void);
void game_update(f32 dt);
void game_set_target(vec3f target);
void game_set_direction(vec3f direction);
void game_destroy(void);
void game_shoot(vec2f pos, f32 rotation, f32 tilt, f32 zoom, f32 ar);
vec3f game_get_player_position(void);

#endif