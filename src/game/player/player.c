#include "player.h"
#include "../game_util.h"
#include <assert.h>

Player player;

void player_update(Player *player, f32 dt)
{
    player->cooldown -= dt;
    player->cooldown2 -= dt;
    if (player->entity != NULL) {
        player->entity->health += player->health_regen * dt;
        if (player->entity->health > player->entity->max_health)
            player->entity->health = player->entity->max_health;
        player->health = player->entity->health;
        player->max_health = player->entity->max_health;
    } else {
        player->health = 0;
    }
    player->mana += player->mana_regen * dt;
    if (player->mana > player->max_mana)
        player->mana = player->max_mana;
}

void player_shoot(Player *player, vec3f direction, vec3f target)
{
    if (player->cooldown < 0) {
        weapon_shoot(player->weapon, player->entity->position, direction, target);
        player->cooldown = 0.5;
    }
}

void player_spellcast(Player *player, vec3f direction, vec3f target)
{
    if (player->cooldown2 < 0 && player->mana >= 1) {
        ability_use(player->ability, player->entity->position, direction, target);
        player->mana -= 1;
        player->cooldown2 = 0.5;
    }
}