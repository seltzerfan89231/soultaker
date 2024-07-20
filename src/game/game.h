#ifndef GAME_H
#define GAME_H

#include "collision.h"
#include "loader/loader.h"
#include "game_util.h"

void game_init(void);
void game_setup(u32 level);
void game_update(f32 dt);
void game_set_target(vec3f target);
void game_set_direction(vec3f direction);
void game_destroy(void);
void game_shoot(vec2f pos, f32 rotation, f32 tilt, f32 zoom, f32 ar);
void game_spellcast(vec2f pos, f32 rotation, f32 tilt, f32 zoom, f32 ar);
vec3f game_get_player_position(void);
void game_pause(void);
void game_switch_weapon(void);
void game_heal(void);
f32 game_get_player_health_ratio(void);
u32 game_get_weapon_tex(void);

#endif