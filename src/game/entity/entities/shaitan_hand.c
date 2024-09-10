#include "../entity.h"
#include "../../projectile/projectile.h"

#define NUM_STATES 1
#define IDLE   0

void shaitan_hand_init_frame_data(FrameData ***frame_data)
{
    frame_data[SHAITAN_HAND] = malloc(4 * sizeof(FrameData*));
    for (i32 i = 0; i < 4; i++)
        frame_data[SHAITAN_HAND][i] = malloc(NUM_STATES * sizeof(FrameData));
    frame_data[SHAITAN_HAND][DOWN][IDLE]  = _FDdef(SHAITAN_HAND_OPEN_LEFT_TEX);
    frame_data[SHAITAN_HAND][RIGHT][IDLE] = _FDdef(SHAITAN_HAND_OPEN_RIGHT_TEX);
    frame_data[SHAITAN_HAND][UP][IDLE]    = _FDdef(SHAITAN_HAND_OPEN_RIGHT_TEX);
    frame_data[SHAITAN_HAND][LEFT][IDLE]  = _FDdef(SHAITAN_HAND_OPEN_LEFT_TEX);
}

void shaitan_hand_destroy_frame_data(FrameData ***frame_data)
{
    for (i32 i = 0; i < 4; i++)
        free(frame_data[SHAITAN_HAND][i]);
    free(frame_data[SHAITAN_HAND]);
}

void shaitan_hand_create(Entity *entity)
{
    entity->scale = 3.0f;
}

void shaitan_hand_update(Entity *entity, f32 dt)
{
    vec2f pivot, pos, rot, dir;
    pivot = vec2f_create(15.5f, 16.5f);
    pos = vec2f_create(entity->position.x, entity->position.z);
    rot = vec2f_rotate(pos, pivot, dt);
    dir = vec2f_normalize(vec2f_sub(rot, pos));
    entity->direction = vec3f_create(dir.x, 0.0, dir.y);
}

void shaitan_hand_damage(Entity *entity, f32 damage)
{
    
}

void shaitan_hand_die(Entity *entity)
{

}