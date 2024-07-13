#include "loader.h"

void load_level(void)
{
    for (i32 i = 0; i < MAP_WIDTH; i++) {
        for (i32 j = 0; j < MAP_WIDTH; j++) {
            /* if (i == 0 || j == 0 || j == MAP_WIDTH - 1 || i == MAP_WIDTH - 1 || (i == 12 && j == 12))
                wall_create(WALL2, i, j, ((int)(i + j)) % 2 == 0 ? 3.0f : 0.8f);
            else
                tile_create(FLOOR, i, j); */
            tile_create(FLOOR, i, j);
        }
    }
            
    player.entity = entity_create(KNIGHT, 1);
    player.weapon.id = 0;
    player.weapon.tex = SWORD_1_TEX;
    player.entity->position = vec3f_create(15.0f, 0.0f, 15.0f);

    Entity* entity = entity_create(ENEMY, 0);
    entity->position = vec3f_create(20, 0, 15);
    entity->scale = 1.0f;

    Obstacle *obstacle = obstacle_create();
    obstacle->position = vec3f_create(10.0f, 0.0f, 10.0f);
    obstacle->hitbox_radius = 0.3f;
    obstacle->scale = 3.0f;

    obstacle = obstacle_create();
    obstacle->position = vec3f_create(12.0f, 0.0f, 10.0f);
    obstacle->hitbox_radius = 0.3f;
    obstacle->scale = 3.0f;

    Parstacle *parstacle = parstacle_create();
    parstacle->position = vec3f_create(20.0f, 0.0f, 20.0f);
    parstacle->scale = 1.8f;
}