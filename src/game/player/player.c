#include "player.h"

Player player;

void player_shoot(Player *player, vec3f direction)
{
    if (game_time - player->cooldown > 0.5) {
        weapon_shoot(player->weapon, player->entity->position, direction);
        player->cooldown = game_time;
    }
}

void player_spellcast(Player *player, vec3f position, vec3f direction)
{
    Particle *part = particle_create();
    part->scale = 0.1;
    part->position = position;
    part->position.y = 0.5;
}