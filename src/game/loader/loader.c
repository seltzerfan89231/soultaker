#include "loader.h"

static void reset(void)
{
    tile_array_destroy(&tiles);
    wall_array_destroy(&walls);
    entity_array_destroy(&entities);
    projectile_array_destroy(&projectiles);
    particle_array_destroy(&particles);
    obstacle_array_destroy(&obstacles);
    parstacle_array_destroy(&parstacles);
    parjicle_array_destroy(&parjicles);
    projectiles = projectile_array_create(0);
    entities = entity_array_create(0);
    particles = particle_array_create(0);
    parjicles = parjicle_array_create(0);
    parstacles = parstacle_array_create(0);
    obstacles = obstacle_array_create(0);
    tiles = tile_array_create(0);
    walls = wall_array_create(0);
    game_time = 0;
}

void load_level1(void)
{
    reset();
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
    player.entity->position = vec3f_create(0.0f, 0.0f, 0.0f);

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

    parstacle_array_update(&parstacles);
    obstacle_array_update(&obstacles);
    tile_array_update(&tiles);
    wall_array_update(&walls);
}

void load_level2(void)
{
    reset();
    for (i32 i = 0; i < MAP_WIDTH; i++) {
        for (i32 j = 0; j < MAP_WIDTH; j++) {
            if (i == 0 || j == 0 || j == MAP_WIDTH - 1 || i == MAP_WIDTH - 1 || (i == 12 && j == 12))
                wall_create(WALL2, i, j, ((int)(i + j)) % 2 == 0 ? 3.0f : 0.8f);
            else
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

    parstacle_array_update(&parstacles);
    obstacle_array_update(&obstacles);
    tile_array_update(&tiles);
    wall_array_update(&walls);
}