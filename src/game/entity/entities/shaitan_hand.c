#include "../entity.h"
#include "../../projectile/projectile.h"

#define NUM_STATES 1
#define IDLE   0

#define NUM_PHASES 3
#define PHASE_1    0
#define PHASE_2    1
#define PHASE_3    2

typedef struct {
    f32 dir_timer;
    bool dir;
    Entity* advisor;
} Data;

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
    entity->data = malloc(sizeof(Data));
    ((Data*)entity->data)->dir_timer = 0;
    ((Data*)entity->data)->dir = TRUE;
}

void shaitan_hand_update(Entity *entity, f32 dt)
{
    Data* data = entity->data;
    vec2f pivot, pos, rot, dir;
    pivot = vec2f_create(15.5f, 16.5f);
    pos = vec2f_create(entity->position.x, entity->position.z);
    rot = vec2f_rotate(pos, pivot, (data->dir) ? dt : -dt);
    dir = vec2f_normalize(vec2f_sub(rot, pos));
    entity->direction = vec3f_create(dir.x, 0.0, dir.y);
    data->dir_timer -= dt;
    if (data->dir_timer < 0) {
        data->dir_timer = 2;
        data->dir = 1 - data->dir;
    }
}

void shaitan_hand_damage(Entity *entity, f32 damage)
{
    
}

void shaitan_hand_die(Entity *entity)
{

}

void shatian_hand_connect_advisor(Entity* hand, Entity* advisor)
{
    Data* data = hand->data;
    data->advisor = advisor;
}