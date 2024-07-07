#ifndef PLAYER_H
#define PLAYER_H

#include "../entity/entity.h"
#include "../projectile/projectile.h"

extern f64 game_time;

typedef struct {
    Entity *entity;
    u32 weapon_id;
    f32 cooldown;
} Player;

void player_shoot(Player *player, vec3f direction);

#endif