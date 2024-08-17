#ifndef PLAYER_H
#define PLAYER_H

#include "../weapon/weapon.h"
#include "../ability/ability.h"
#include "../entity/entity.h"
#include "../projectile/projectile.h"

extern f32 game_time;

typedef struct {
    Entity *entity;
    Weapon weapon;
    Ability ability;
    f32 mana, max_mana, mana_regen, health, max_health, health_regen;
    f32 cooldown, cooldown2;
} Player;

extern Player player;

void player_update(Player *player, f32 dt);
void player_shoot(Player *player, vec3f direction, vec3f target);
void player_spellcast(Player *player, vec3f direction, vec3f target);

#endif