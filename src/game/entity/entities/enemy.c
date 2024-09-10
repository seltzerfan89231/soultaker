#include "../entity.h"
#include "../../player/player.h"
#include "../../projectile/projectile.h"

extern f32 game_time;

#define NUM_STATES 1
#define IDLE   0

void enemy_init_frame_data(FrameData ***frame_data)
{
    frame_data[ENEMY] = malloc(4 * sizeof(FrameData*));
    for (i32 i = 0; i < 4; i++)
        frame_data[ENEMY][i] = malloc(NUM_STATES * sizeof(FrameData));
    frame_data[ENEMY][DOWN][IDLE]  = _FDdef(KNIGHT_IDLE_DOWN_TEX);
    frame_data[ENEMY][RIGHT][IDLE] = _FDdef(KNIGHT_IDLE_RIGHT_TEX);
    frame_data[ENEMY][UP][IDLE]    = _FDdef(KNIGHT_IDLE_UP_TEX);
    frame_data[ENEMY][LEFT][IDLE]  = _FDdef(KNIGHT_IDLE_LEFT_TEX);
}

void enemy_destroy_frame_data(FrameData ***frame_data)
{
    for (i32 i = 0; i < 4; i++)
        free(frame_data[ENEMY][i]);
    free(frame_data[ENEMY]);
}

void enemy_create(Entity *entity)
{
    entity->health = 100;
    entity->max_health = 100;
}

void enemy_update(Entity *entity, f32 dt)
{
    if (player.entity == NULL) {
        entity->direction = vec3f_create(0, 0, 0);
        return;
    }
    entity->speed = 0.5;
    entity->direction = vec3f_normalize(vec3f_sub(player.entity->position, entity->position));
    entity->facing = vec2f_create(entity->direction.x, entity->direction.z);
    if (entity->timer >= 0.05) {
        entity->timer = 0;
        for (i32 i = 0; i < 8; i++) {
            Projectile* proj = projectile_create(DEFAULT_PROJ, FALSE, FALSE);
            proj->tex = BULLET_TEX;
            proj->position = entity->position;
            proj->rotation = i * 0.8 + sin(game_time);
            proj->direction = vec3f_create(cos(proj->rotation), 0.0f, sin(proj->rotation));
            proj->scale = 1.0f;
            proj->lifetime = 3.0f;
            proj->hitbox_radius = (proj->scale - 0.4) / 2;
            proj->position.y = 0.5f;
        }
    }
}

void enemy_damage(Entity *entity, f32 damage)
{
    
}

void enemy_die(Entity *entity)
{}