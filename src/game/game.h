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
#include "player/player.h"
#include "../util/array.h"

#define MAP_WIDTH 50

void game_init(void);
void game_setup(void);
void game_update(f32 dt);
void game_set_target(vec3f target);
void game_set_direction(vec3f direction);
void game_destroy(void);
void game_shoot(vec2f pos, f32 rotation, f32 tilt, f32 zoom, f32 ar);
vec3f game_get_player_position(void);
void game_pause(void);
u32 game_switch_weapon(void);

#endif