#include "player.h"
#include <assert.h>

Player player;

void player_update(Player *player, f32 dt)
{
    player->cooldown -= dt;
    player->cooldown2 -= dt;
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
    if (player->cooldown2 < 0) {
        ability_use(player->ability, player->entity->position, direction, target);
        player->cooldown2 = 0.5;
    }
}