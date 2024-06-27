#ifndef GAME_H
#define GAME_H

#include "array.h"

#define MAP_WIDTH 50

typedef struct {
    ProjectileArray projectiles;
    EntityArray entities;
    ParticleArray particles;
    ParjicleArray parjicles;
    ParstacleArray parstacles;
    ObstacleArray obstacles;
    TileArray tiles;
    WallArray walls;
} Game;

extern Game game;

void game_init(void);
void game_setup(void);
void game_update(f32 dt);
void game_set_target(vec3f target);
void game_set_direction(vec3f direction);
void game_destroy(void);
void game_shoot(vec2f pos, f32 rotation, f32 tilt, f32 zoom, f32 ar);
void game_idle(void);
void game_set_state(u32 state);

#endif