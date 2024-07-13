#include "player.h"

Player player;

void player_shoot(Player *player, vec3f direction)
{
    if (game_time - player->cooldown > 0.5) {
        weapon_shoot(player->weapon, player->entity->position, direction);
        player->cooldown = game_time;
    }
}