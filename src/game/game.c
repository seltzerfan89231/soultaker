#include "game.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <sys/time.h>
#include <pthread.h>   
#include <semaphore.h>  
#include <Windows.h>

f32 game_time;
f32 game_dt;
bool game_paused;

static pthread_t thread_id;
static bool kill_thread;
static sem_t mutex;

extern void collide_objects(f32 dt);
extern void update_objects(f32 dt);

static void *game_update(void *vargp)
{
    while (!kill_thread) {
        struct timeval start, end;
        i64 seconds, microseconds;
        
        if (game_dt > 0.0001) {
            gettimeofday(&start, NULL);
            if (!game_paused) {
                game_time += game_dt;
                sem_wait(&mutex);
                update_objects(game_dt);
                collide_objects(game_dt);
                /* wall_array_update(&global_walls);
                tile_array_update(&global_tiles);
                obstacle_array_update(&global_obstacles);
                parstacle_array_update(&global_parstacles); */
                entity_array_update(&global_entities);
                projectile_array_update(&global_projectiles);
                particle_array_update(&global_particles);
                parjicle_array_update(&global_parjicles);
                sem_post(&mutex);
            }
        }

        gettimeofday(&end, NULL);
        seconds = end.tv_sec - start.tv_sec;
        microseconds = end.tv_usec - start.tv_usec;
        game_dt = seconds + microseconds*1e-6;
    }
}

void game_init(void)
{
    aud_init();
    tilemap_init();
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
        case 3:
            load_level3(); break;
        case 4:
            load_level4(); break;
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

    aud_destroy();
    tilemap_destroy();
    destroy_all_tiles();
    destroy_all_walls();
    destroy_all_entities();
    destroy_all_projectiles();
    destroy_all_particles();
    destroy_all_obstacles();
    destroy_all_parstacles();
    destroy_all_parjicles();
}

void game_shoot(vec2f cursor_position, f32 rotation, f32 tilt, f32 zoom, f32 ar)
{
    sem_wait(&mutex);
    if (player.entity == NULL || game_paused) {
        sem_post(&mutex);
        return;
    }
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
    sem_post(&mutex);
}

void game_spellcast(vec2f cursor_position, f32 rotation, f32 tilt, f32 zoom, f32 ar)
{
    sem_wait(&mutex);
    if (player.entity == NULL || game_paused) {
        sem_post(&mutex);
        return;
    }
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
    sem_post(&mutex);
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
    if (player.entity == NULL)
        return;
    player.entity->health = player.entity->max_health;
}

void game_kill(void)
{
    if (player.entity == NULL)
        return;
    player.entity->health = 0;
}

f32 game_get_player_health_ratio(void)
{
    if (player.entity == NULL)
        return 0;
    return (f32)player.entity->health / player.entity->max_health;
}

f32 game_get_player_mana_ratio(void)
{
    if (player.entity == NULL)
        return 0;
    return player.mana / player.max_mana;
}

u32 game_get_weapon_tex(void)
{
    return player.weapon.tex;
}

Entity* game_get_current_boss(void)
{
    return boss;
}

void game_wait(void)
{
    sem_wait(&mutex);
}

void game_post(void)
{
    sem_post(&mutex);
}