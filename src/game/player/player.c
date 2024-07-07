#include "player.h"

void player_shoot(Player *player, vec3f direction)
{
    if (game_time - player->cooldown > 0.5) {
        Projectile* proj = projectile_create(SWORD, TRUE);
        proj->speed = 10;
        proj->position = player->entity->position;
        f32 t = atan(direction.z / direction.x);
        proj->rotation = t + (direction.x > 0 ? 0 : PI);
        proj->direction = direction;
        proj->position.y = 0.5f;
        player->cooldown = game_time;
    }
    
}