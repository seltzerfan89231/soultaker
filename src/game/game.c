#include "game.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <sys/time.h>
#include <pthread.h>   
#include <semaphore.h>  

f64 game_time;
f64 game_dt;
bool game_paused;

static pthread_t thread_id;
static bool kill_thread;
static sem_t mutex;

extern void collide_objects(f32 dt);
extern void update_objects(f32 dt);

static void *game_update(void *vargp)
{
    while (TRUE) {
        if (kill_thread)
            pthread_exit(NULL);

        if (game_paused)
            continue;
        
        sem_wait(&mutex);

        game_time += game_dt;

        struct timeval start, end;
        gettimeofday(&start, NULL);

        update_objects(game_dt);
        collide_objects(game_dt);
        
        entity_array_update(&entities);
        projectile_array_update(&projectiles);
        particle_array_update(&particles);
        parjicle_array_update(&parjicles);
        
        gettimeofday(&end, NULL);
        long seconds = end.tv_sec - start.tv_sec;
        long microseconds = end.tv_usec - start.tv_usec;
        double time_taken = seconds + microseconds*1e-6;
        game_dt = time_taken;

        sem_post(&mutex); 
    }
}

void game_init(void)
{
    projectiles = projectile_array_create(0);
    entities = entity_array_create(0);
    particles = particle_array_create(0);
    parjicles = parjicle_array_create(0);
    parstacles = parstacle_array_create(0);
    obstacles = obstacle_array_create(0);
    tiles = tile_array_create(0);
    walls = wall_array_create(0);
    game_paused = TRUE;
    kill_thread = FALSE;
    sem_init(&mutex, 0, 1);
    pthread_create(&thread_id, NULL, game_update, NULL);
}

void game_setup(u32 level)
{
    game_time = 0;
    game_dt = 0;
    game_paused = TRUE;
    sem_wait(&mutex);
    switch (level) {
        case 1:
            load_level1(); break;
        case 2:
            load_level2(); break;
    }
    sem_post(&mutex);
    game_paused = FALSE;
}

void game_set_direction(vec3f direction)
{
    if (player.entity == NULL  || game_paused)
        return;
    assert(player.entity != NULL);
    entity_set_direction(player.entity, direction);
}

void game_set_target(vec3f target)
{
    if (game_paused)
        return;
    assert(player.entity != NULL);
    player.entity->position = target;
}

void game_destroy(void)
{
    kill_thread = TRUE;
    pthread_join(thread_id, NULL);
    sem_destroy(&mutex);

    tile_array_destroy(&tiles);
    wall_array_destroy(&walls);
    entity_array_destroy(&entities);
    projectile_array_destroy(&projectiles);
    particle_array_destroy(&particles);
    obstacle_array_destroy(&obstacles);
    parstacle_array_destroy(&parstacles);
    parjicle_array_destroy(&parjicles);
}

void game_shoot(vec2f cursor_position, f32 rotation, f32 tilt, f32 zoom, f32 ar)
{
    if (player.entity == NULL || game_paused)
        return;
    assert(player.entity != NULL);
    f32 dirx, dirz, a, b, c, r, ratio;
    vec3f direction, target;
    vec2f pos = vec2f_create((cursor_position.x - 0.5) * ar, cursor_position.y - 0.5 + 1.0 / 4 / zoom);
    r = vec2f_mag(pos);
    a = atan(pos.y/pos.x);
    b = PI/2 - tilt;
    c = tan(a) * tan(a) / cos(b) / cos(b) + 1;
    ratio = sqrt(r*r/(c * cos(a) * cos(a)));
    pos.x =  pos.x > 0 ? 1 / sqrt(c) : -1 / sqrt(c);
    pos.y = -pos.y > 0 ? sqrt(1 - 1 / c) : -sqrt(1 - 1 / c);
    dirx = pos.x * cos(rotation - HALFPI) - pos.y * sin(rotation - HALFPI);
    dirz = pos.x * sin(rotation - HALFPI) + pos.y * cos(rotation - HALFPI);
    direction = vec3f_normalize(vec3f_create(dirx, 0.0, dirz));
    target = vec3f_sub(player.entity->position, vec3f_scale(-2 * zoom * r * r / ratio, direction));
    player_shoot(&player, direction, target);
    player.entity->facing = vec2f_normalize(vec2f_create(dirx, dirz));
    player.entity->flag = TRUE;
}

void game_spellcast(vec2f cursor_position, f32 rotation, f32 tilt, f32 zoom, f32 ar)
{
    if (player.entity == NULL || game_paused)
        return;
    assert(player.entity != NULL);
    f32 dirx, dirz, a, b, c, r, ratio;
    vec3f direction, target;
    vec2f pos = vec2f_create((cursor_position.x - 0.5) * ar, cursor_position.y - 0.5 + 1.0 / 4 / zoom);
    r = vec2f_mag(pos);
    a = atan(pos.y/pos.x);
    b = PI/2 - tilt;
    c = tan(a) * tan(a) / cos(b) / cos(b) + 1;
    ratio = sqrt(r*r/(c * cos(a) * cos(a)));
    pos.x =  pos.x > 0 ? 1 / sqrt(c) : -1 / sqrt(c);
    pos.y = -pos.y > 0 ? sqrt(1 - 1 / c) : -sqrt(1 - 1 / c);
    dirx = pos.x * cos(rotation - HALFPI) - pos.y * sin(rotation - HALFPI);
    dirz = pos.x * sin(rotation - HALFPI) + pos.y * cos(rotation - HALFPI);
    direction = vec3f_normalize(vec3f_create(dirx, 0.0, dirz));
    target = vec3f_sub(player.entity->position, vec3f_scale(-2 * zoom * r * r / ratio, direction));
    player_spellcast(&player, direction, target);
    player.entity->facing = vec2f_normalize(vec2f_create(dirx, dirz));
    player.entity->flag = TRUE;
}

vec3f game_get_player_position(void)
{
    assert(player.entity != NULL);
    return player.entity->position;
}

void game_pause(void)
{
    game_paused = 1 - game_paused;
}

void game_switch_weapon(void)
{
    if (player.entity == NULL || game_paused)
        return;
    assert(player.entity != NULL);
    player.weapon.id = 1 - player.weapon.id;
    if (player.weapon.id == SWORD)
        player.weapon.tex = SWORD_1_TEX;
    if (player.weapon.id == SWORD2)
        player.weapon.tex = SWORD_2_TEX;
}

void game_heal(void)
{
    if (player.entity == NULL || game_paused)
        return;
    assert(player.entity != NULL);
    player.entity->health = player.entity->max_health;
}

f32 game_get_player_health_ratio(void)
{
    if (player.entity == NULL || game_paused)
        return 0;
    assert(player.entity != NULL);
    return player.entity->health / player.entity->max_health;
}

f32 game_get_player_mana_ratio(void)
{
    if (player.entity == NULL || game_paused)
        return 0;
    assert(player.entity != NULL);
    return player.mana / player.max_mana;
}

u32 game_get_weapon_tex(void)
{
    if (game_paused)
        return 0;
    return player.weapon.tex;
}