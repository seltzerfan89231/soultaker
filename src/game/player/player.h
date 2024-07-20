#ifndef PLAYER_H
#define PLAYER_H

#include "../weapon/weapon.h"
#include "../entity/entity.h"
#include "../projectile/projectile.h"

extern f64 game_time;

typedef struct {
    Entity *entity;
    Weapon weapon;
    f32 cooldown;
} Player;

extern Player player;

void player_shoot(Player *player, vec3f direction);
void player_spellcast(Player *player, vec3f position, vec3f direction);

#endif