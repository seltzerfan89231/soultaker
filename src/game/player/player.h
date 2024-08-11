#ifndef PLAYER_H
#define PLAYER_H

#include "../weapon/weapon.h"
#include "../ability/ability.h"
#include "../entity/entity.h"
#include "../projectile/projectile.h"

extern f64 game_time;

typedef struct {
    Entity *entity;
    Weapon weapon;
    Ability ability;
    f32 cooldown, cooldown2;
} Player;

extern Player player;

void player_update(Player *player, f32 dt);
void player_shoot(Player *player, vec3f direction, vec3f target);
void player_spellcast(Player *player, vec3f direction, vec3f target);

#endif