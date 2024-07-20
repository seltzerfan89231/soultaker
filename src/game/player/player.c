#include "player.h"

Player player;

void player_shoot(Player *player, vec3f direction, vec3f target)
{
    if (game_time - player->cooldown > 0.5) {
        weapon_shoot(player->weapon, player->entity->position, direction, target);
        player->cooldown = game_time;
    }
}

void player_spellcast(Player *player, vec3f direction, vec3f target)
{
    if (game_time - player->cooldown2 > 0.5) {
        ability_use(player->ability, player->entity->position, direction, target);
        player->cooldown2 = game_time;
    }
}