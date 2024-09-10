#include "../entity.h"

#define NUM_STATES  5
#define IDLE    0
#define WALK_1  1
#define WALK_2  2
#define SHOOT_1 3
#define SHOOT_2 4

typedef struct {
    f32 timer;
} Data;

void knight_init_frame_data(FrameData ***frame_data)
{
    frame_data[KNIGHT] = malloc(4 * sizeof(FrameData*));
    for (i32 i = 0; i < 4; i++)
        frame_data[KNIGHT][i] = malloc(NUM_STATES * sizeof(FrameData));
    frame_data[KNIGHT][DOWN][IDLE]  = _FDdef(KNIGHT_IDLE_DOWN_TEX);
    frame_data[KNIGHT][RIGHT][IDLE] = _FDdef(KNIGHT_IDLE_RIGHT_TEX);
    frame_data[KNIGHT][UP][IDLE]    = _FDdef(KNIGHT_IDLE_UP_TEX);
    frame_data[KNIGHT][LEFT][IDLE]  = _FDdef(KNIGHT_IDLE_LEFT_TEX);

    frame_data[KNIGHT][DOWN][WALK_1]  = _FDdef(KNIGHT_WALK_DOWN_1_TEX);
    frame_data[KNIGHT][RIGHT][WALK_1] = _FDdef(KNIGHT_IDLE_RIGHT_TEX);
    frame_data[KNIGHT][UP][WALK_1]    = _FDdef(KNIGHT_WALK_UP_1_TEX);
    frame_data[KNIGHT][LEFT][WALK_1]  = _FDdef(KNIGHT_IDLE_LEFT_TEX);

    frame_data[KNIGHT][DOWN][WALK_2]  = _FDdef(KNIGHT_WALK_DOWN_2_TEX);
    frame_data[KNIGHT][RIGHT][WALK_2] = _FDdef(KNIGHT_WALK_RIGHT_TEX);
    frame_data[KNIGHT][UP][WALK_2]    = _FDdef(KNIGHT_WALK_UP_2_TEX);
    frame_data[KNIGHT][LEFT][WALK_2]  = _FDdef(KNIGHT_WALK_LEFT_TEX);

    frame_data[KNIGHT][DOWN][SHOOT_1]  = _FDdef(KNIGHT_SHOOT_DOWN_1_TEX);
    frame_data[KNIGHT][RIGHT][SHOOT_1] = _FDdef(KNIGHT_SHOOT_RIGHT_1_TEX);
    frame_data[KNIGHT][UP][SHOOT_1]    = _FDdef(KNIGHT_SHOOT_UP_1_TEX);
    frame_data[KNIGHT][LEFT][SHOOT_1]  = _FDdef(KNIGHT_SHOOT_LEFT_1_TEX);

    frame_data[KNIGHT][DOWN][SHOOT_2]   = _FD(0.0f, 0.0f, 1.0f, 1.0f, KNIGHT_SHOOT_DOWN_2_TEX);
    frame_data[KNIGHT][RIGHT][SHOOT_2]  = _FD(1.5f / 8.0f, 0.0f, 11.0f / 8.0f, 1.0f, KNIGHT_SHOOT_RIGHT_2_TEX);
    frame_data[KNIGHT][UP][SHOOT_2]     = _FD(0.0f, 0.0f, 1.0f, 1.0f, KNIGHT_SHOOT_UP_2_TEX);
    frame_data[KNIGHT][LEFT][SHOOT_2]   = _FD(-1.5f / 8.0f, 0.0f, 11.0f / 8.0f, 1.0f, KNIGHT_SHOOT_LEFT_2_TEX);
}

void knight_destroy_frame_data(FrameData ***frame_data)
{
    for (i32 i = 0; i < 4; i++)
        free(frame_data[KNIGHT][i]);
    free(frame_data[KNIGHT]);
}

void knight_create(Entity *entity)
{
    entity->data = malloc(sizeof(Data));
}

void knight_update(Entity *entity, f32 dt)
{
    Data* data = entity->data;
    if (entity->flag == TRUE) {
        if (entity->state != SHOOT_1 && entity->state != SHOOT_2) {
            entity->state = SHOOT_1;
            data->timer = 0;
            entity->face_dir = FALSE;
        }
        entity->flag = FALSE;
    } else {
        if (entity->state == SHOOT_2) {
            if (data->timer > 0.15) {
                entity->state = IDLE;
                data->timer = 0;
                entity->face_dir = TRUE;
            }
        }
    }
    
    if (vec3f_mag(entity->direction) == 0) {
        if (entity->state == WALK_1 || entity->state == WALK_2)
            entity->state = IDLE;
    }
    else {
        if (entity->state == IDLE)
            entity->state = WALK_1;
    }

    switch (entity->state) {
        case WALK_1:
            if (data->timer > 0.15) {
                data->timer = 0;
                entity->state = WALK_2;
            }
            break;
        case WALK_2:
            if (data->timer > 0.15) {
                data->timer = 0;
                entity->state = WALK_1;
            }
            break;
        case SHOOT_1:
            if (data->timer > 0.15) {
                data->timer = 0;
                entity->state = SHOOT_2;
            }
            break;
        case SHOOT_2:
            if (data->timer > 0.15) {
                data->timer = 0;
                entity->state = SHOOT_1;
            }
            break;
        default:
            break;
    }
    data->timer -= dt;
}

void knight_damage(Entity *entity, f32 damage)
{
    
}

void knight_die(Entity *entity)
{
    Parstacle *parstacle = parstacle_create();
    parstacle->tex = GRAVESTONE_TEX;
    parstacle->position = entity->position;
}