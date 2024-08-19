#include "loader.h"

static void reset(void)
{
    aud_clear();
    destroy_all_tiles();
    destroy_all_walls();
    destroy_all_parstacles();
    destroy_all_entities();
    destroy_all_projectiles();
    destroy_all_particles();
    destroy_all_obstacles();
    destroy_all_parjicles();
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

static void fill_tilemap(void)
{

}

void load_level1(void)
{
    reset();
    tilemap_reset(10, 10);
    for (i32 i = 0; i < 10; i++) {
        for (i32 j = 0; j < 10; j++) {
            if (i == 1 && j == 1)
                wall_create(WALL2, i, j , 3);
            else
                tile_create(GRASS, i, j);
        }
    }
            
    player.entity = entity_create(KNIGHT, TRUE);
    player.entity->speed = 8;
    player.entity->health = player.entity->max_health = 10;
    player.mana = player.max_mana = 10;
    player.mana_regen = player.health_regen = 0.5;
    player.weapon.id = 0;
    player.weapon.tex = SWORD_1_TEX;
    player.entity->position = vec3f_create(5.0f, 0.0f, 5.0f);

    for (i32 i = 0; i < 0; i++) {
        Obstacle *obstacle = obstacle_create();
        obstacle->position = vec3f_create((f32)rand() / RAND_MAX * MAP_WIDTH, 0.0f, (f32)rand() / RAND_MAX * MAP_WIDTH);
        obstacle->hitbox_radius = 0.3f;
        obstacle->scale = 3.0f;
    }

    for (i32 i = 0; i < 0; i++) {
        Entity *entity = entity_create(SLIME, FALSE);
        entity->max_health = entity->health = 10;
        entity->position = vec3f_create((f32)rand() / RAND_MAX * MAP_WIDTH, 0.0f, (f32)rand() / RAND_MAX * MAP_WIDTH);
    }

    for (i32 i = 0; i < 0; i++) {
        Parstacle *parstacle = parstacle_create();
        parstacle->position = vec3f_create((f32)rand() / RAND_MAX * MAP_WIDTH, 0.0f, (f32)rand() / RAND_MAX * MAP_WIDTH);
        parstacle->scale = 1 + (f32)rand() / RAND_MAX;
    }

    parstacle_array_update(&parstacles);
    obstacle_array_update(&obstacles);
    tile_array_update(&tiles);
    wall_array_update(&walls);
}

void load_level2(void)
{
    reset();
    tilemap_reset(MAP_WIDTH, MAP_WIDTH);
    for (i32 i = 0; i < MAP_WIDTH; i++) {
        for (i32 j = 0; j < MAP_WIDTH; j++) {
            if (i == 0 || j == 0 || i == MAP_WIDTH - 1 || j == MAP_WIDTH - 1)
                wall_create(WALL2, i, j, 3.0);
            else
                tile_create(GRASS, i, j);
        }
    }
            
    player.entity = entity_create(KNIGHT, TRUE);
    player.entity->speed = 8;
    player.entity->health = player.entity->max_health = 100000;
    player.mana = player.max_mana = 10;
    player.mana_regen = player.health_regen = 0.5;
    player.weapon.id = 0;
    player.weapon.tex = SWORD_1_TEX;
    player.entity->position = vec3f_create(20.0f, 0.0f, 20.0f);

    for (i32 i = 0; i < 20; i++) {
        Entity* entity = entity_create(ENEMY, 0);
        entity->position = vec3f_create(20 + i, 0, 15);
        entity->scale = 1.0f;
    }

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