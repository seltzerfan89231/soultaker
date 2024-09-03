#include "loader.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

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
    global_projectiles = projectile_array_create(0, 100);
    global_entities = entity_array_create(0, 100);
    global_particles = particle_array_create(0, 100);
    global_parjicles = parjicle_array_create(0, 100);
    global_parstacles = parstacle_array_create(0, 100);
    global_obstacles = obstacle_array_create(0, 100);
    global_tiles = tile_array_create(0, 1);
    global_walls = wall_array_create(0, 1);
    game_time = 0;
}

void load_level1(void)
{
    reset();
    tilemap_reset(MAP_WIDTH, MAP_WIDTH);
    for (i32 i = 0; i < MAP_WIDTH; i++) {
        for (i32 j = 0; j < MAP_WIDTH; j++) {
            if (i == 1 && j == 1)
                wall_create(DEFAULT_WALL, i, j, 1, 3, 1);
            else if (i >= 10 && i < 20 && j >= 10 && j < 20)
                tile_create(HELLSTONE, i, j);
            else
                tile_create(GRASS, i, j);
        }
    }
    tile_create(GRASS, -30, -100);
            
    player.entity = entity_create(KNIGHT, TRUE);
    player.entity->speed = 8;
    player.entity->health = player.entity->max_health = 10;
    player.mana = player.max_mana = 10;
    player.mana_regen = player.health_regen = 0.5;
    player.weapon.id = 0;
    player.weapon.tex = SWORD_1_TEX;
    player.entity->position = vec3f_create(5.0f, 0.0f, 5.0f);

    for (i32 i = 0; i < 600; i++) {
        Obstacle *obstacle = obstacle_create((f32)rand() / RAND_MAX * MAP_WIDTH, (f32)rand() / RAND_MAX * MAP_WIDTH);
        obstacle->hitbox_radius = 0.3f;
        obstacle->scale = 3.0f;
    }

    for (i32 i = 0; i < 1000; i++) {
        Entity *entity = entity_create(SLIME, FALSE);
        entity->max_health = entity->health = 10;
        entity->position = vec3f_create((f32)rand() / RAND_MAX * MAP_WIDTH, 0.0f, (f32)rand() / RAND_MAX * MAP_WIDTH);
    }

    for (i32 i = 0; i < 600; i++) {
        Parstacle *parstacle = parstacle_create();
        parstacle->position = vec3f_create((f32)rand() / RAND_MAX * MAP_WIDTH, 0.0f, (f32)rand() / RAND_MAX * MAP_WIDTH);
        parstacle->scale = 1 + (f32)rand() / RAND_MAX;
    }

    parstacle_array_update(&global_parstacles);
    obstacle_array_update(&global_obstacles);
    tile_array_update(&global_tiles);
    wall_array_update(&global_walls);
}

void load_level2(void)
{
    reset();
    tilemap_reset(MAP_WIDTH, MAP_WIDTH);
    for (i32 i = 0; i < MAP_WIDTH; i++) {
        for (i32 j = 0; j < MAP_WIDTH; j++) {
            if (i == 0 || j == 0 || i == MAP_WIDTH - 1 || j == MAP_WIDTH - 1)
                wall_create(DEFAULT_WALL, i, j, 1, 3, 1);
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

    for (i32 i = 0; i < 10000; i++) {
        Obstacle *obstacle = obstacle_create((f32)rand() / RAND_MAX * MAP_WIDTH, (f32)rand() / RAND_MAX * MAP_WIDTH);
        obstacle->hitbox_radius = 0.3f;
        obstacle->scale = 3.0f;
    }

    Parstacle *parstacle = parstacle_create();
    parstacle->position = vec3f_create(20.0f, 0.0f, 20.0f);
    parstacle->scale = 1.8f;

    parstacle_array_update(&global_parstacles);
    obstacle_array_update(&global_obstacles);
    tile_array_update(&global_tiles);
    wall_array_update(&global_walls);
}

void load_level3(void)
{
    reset();
    tilemap_reset(MAP_WIDTH, MAP_WIDTH);
    for (i32 i = 0; i < MAP_WIDTH; i++) {
        for (i32 j = 0; j < MAP_WIDTH; j++) {
            if (i == 0 || j == 0 || i == MAP_WIDTH - 1 || j == MAP_WIDTH - 1)
                wall_create(DEFAULT_WALL, i, j, 1, 3, 1);
            else
                tile_create(GRASS, i, j);
        }
    }
    Wall *wall = wall_create(DEFAULT_WALL, 23.0, 3.0, 5.0, 3.0, 5.0f);

    player.entity = entity_create(KNIGHT, TRUE);
    player.entity->speed = 8;
    player.entity->health = player.entity->max_health = 100000;
    player.mana = player.max_mana = 10;
    player.mana_regen = player.health_regen = 0.5;
    player.weapon.id = 0;
    player.weapon.tex = SWORD_1_TEX;
    player.entity->position = vec3f_create(20.0f, 0.0f, 20.0f);

    for (i32 i = 0; i < 10; i++) {
        Entity* entity = entity_create(TRAINING_DUMMY, 0);
        entity->position = vec3f_create(20 + i, 0, 15);
        entity->scale = 1.0f;
    }

    parstacle_array_update(&global_parstacles);
    obstacle_array_update(&global_obstacles);
    tile_array_update(&global_tiles);
    wall_array_update(&global_walls);
}

static char* read_map(char *path)
{
    FILE *ptr;
    char *content;
    ptr = fopen(path, "r");
    fseek(ptr, 0, SEEK_END);
    i32 len = ftell(ptr);
    if (len == 0) {
        printf("File %s is empty", path);
        return NULL;
    }
    fseek(ptr, 0, SEEK_SET);
    content = calloc(len, sizeof(char));
    fread(content, 1, len, ptr);
    fclose(ptr);
    return content;
}

void load_level4(void)
{
    reset();
    tilemap_reset(31, 37);
    char *map = read_map("src/game/loader/shaitan.txt");
    i32 x, z, i;
    for (x = i = 0, z = 36; i < strlen(map); i++) {
        if (map[i] == '1')
            wall_create(SHAITAN_WALL, x, z, 1, 2, 1);
        if (map[i] == '2') {
            wall_create(SHAITAN_BARS, x, z + 0.5, 1, 2, 0);
            tile_create(SHAITAN_HELLSTONE, x, z);
        }
        if (map[i] == '3')
            tile_create(SHAITAN_FLOOR, x, z);
        if (map[i] == '4') {
            Tile *t = tile_create(SHAITAN_LAVA, x, z);
            tile_set_offset(t, 3);
        }
        if (map[i] == '5')
            tile_create(SHAITAN_HELLSTONE, x, z);
        if (map[i] == '\n')
            x = 0, z--;
        else
            x++;
    }
    free(map);

    for (x = 0; x < 31; x++) {
        for (z = 0; z < 37; z++) {
            Tile *tile = tilemap_get_tile(x, z);
            if (tile == NULL || tile->id == SHAITAN_LAVA)
                continue;
            Tile *down = tilemap_get_tile(x, z-1);
            Tile *right = tilemap_get_tile(x+1, z);
            Tile *up = tilemap_get_tile(x, z+1);
            Tile *left = tilemap_get_tile(x-1, z);
            if (down != NULL && down->id == SHAITAN_LAVA)
                tile_set_shadow(tile, DOWN);
            if (up != NULL && up->id == SHAITAN_LAVA)
                tile_set_shadow(tile, UP);
            if (right != NULL && right->id == SHAITAN_LAVA)
                tile_set_shadow(tile, RIGHT);
            if (left != NULL && left->id == SHAITAN_LAVA)
                tile_set_shadow(tile, LEFT);
        }
    }

    for (x = 0; x < 31; x++) {
        for (z = 0; z < 37; z++) {
            Wall *wall = tilemap_get_wall(x, z);
            if (wall == NULL || wall->id != SHAITAN_WALL)
                continue;
            Wall *down = tilemap_get_wall(x, z-1);
            Wall *right = tilemap_get_wall(x+1, z);
            Wall *up = tilemap_get_wall(x, z+1);
            Wall *left = tilemap_get_wall(x-1, z);
            if (down != NULL && down->id == SHAITAN_WALL)
                wall_set_blocked(wall, DOWN);
            if (up != NULL && up->id == SHAITAN_WALL)
                wall_set_blocked(wall, UP);
            if (right != NULL && right->id == SHAITAN_WALL)
                wall_set_blocked(wall, RIGHT);
            if (left != NULL && left->id == SHAITAN_WALL)
                wall_set_blocked(wall, LEFT);
        }
    }

    player.entity = entity_create(KNIGHT, TRUE);
    player.entity->speed = 8;
    player.entity->health = player.entity->max_health = 10;
    player.mana = player.max_mana = 10;
    player.mana_regen = player.health_regen = 0.5;
    player.weapon.id = 0;
    player.weapon.tex = SWORD_1_TEX;
    player.entity->position = vec3f_create(15.5, 0.0f, 12);
}