#include "../entity.h"
#include <stdio.h>

void knight_init_frame_data(FrameData ***frame_data)
{
    frame_data[KNIGHT] = malloc(4 * sizeof(FrameData*));
    for (i32 i = 0; i < 4; i++)
        frame_data[KNIGHT][i] = malloc(KNIGHT_STATES * sizeof(FrameData));
    frame_data[KNIGHT][DOWN][KNIGHT_IDLE]  = _FDdef(KNIGHT_IDLE_DOWN_TEX);
    frame_data[KNIGHT][RIGHT][KNIGHT_IDLE] = _FDdef(KNIGHT_IDLE_RIGHT_TEX);
    frame_data[KNIGHT][UP][KNIGHT_IDLE]    = _FDdef(KNIGHT_IDLE_UP_TEX);
    frame_data[KNIGHT][LEFT][KNIGHT_IDLE]  = _FDdef(KNIGHT_IDLE_LEFT_TEX);

    frame_data[KNIGHT][DOWN][KNIGHT_WALK_1] = (FrameData) {
        .x = 0.0f, .y = 0.0f, .w = 1.0f, .h = 1.0f,
        .frame = KNIGHT_WALK_DOWN_1_TEX
    };
    frame_data[KNIGHT][RIGHT][KNIGHT_WALK_1] = (FrameData) {
        .x = 0.0f, .y = 0.0f, .w = 1.0f, .h = 1.0f,
        .frame = KNIGHT_IDLE_RIGHT_TEX
    };
    frame_data[KNIGHT][UP][KNIGHT_WALK_1] = (FrameData) {
        .x = 0.0f, .y = 0.0f, .w = 1.0f, .h = 1.0f,
        .frame = KNIGHT_WALK_UP_1_TEX
    };
    frame_data[KNIGHT][LEFT][KNIGHT_WALK_1] = (FrameData) {
        .x = 0.0f, .y = 0.0f, .w = 1.0f, .h = 1.0f,
        .frame = KNIGHT_IDLE_LEFT_TEX
    };

    frame_data[KNIGHT][DOWN][KNIGHT_WALK_2] = (FrameData) {
        .x = 0.0f, .y = 0.0f, .w = 1.0f, .h = 1.0f,
        .frame = KNIGHT_WALK_DOWN_2_TEX
    };
    frame_data[KNIGHT][RIGHT][KNIGHT_WALK_2] = (FrameData) {
        .x = 0.0f, .y = 0.0f, .w = 1.0f, .h = 1.0f,
        .frame = KNIGHT_WALK_RIGHT_TEX
    };
    frame_data[KNIGHT][UP][KNIGHT_WALK_2] = (FrameData) {
        .x = 0.0f, .y = 0.0f, .w = 1.0f, .h = 1.0f,
        .frame = KNIGHT_WALK_UP_2_TEX
    };
    frame_data[KNIGHT][LEFT][KNIGHT_WALK_2] = (FrameData) {
        .x = 0.0f, .y = 0.0f, .w = 1.0f, .h = 1.0f,
        .frame = KNIGHT_WALK_LEFT_TEX
    };

    frame_data[KNIGHT][DOWN][KNIGHT_SHOOT_1] = (FrameData) {
        .x = 0.0f, .y = 0.0f, .w = 1.0f, .h = 1.0f,
        .frame = KNIGHT_SHOOT_DOWN_1_TEX
    };
    frame_data[KNIGHT][RIGHT][KNIGHT_SHOOT_1] = (FrameData) {
        .x = 0.0f, .y = 0.0f, .w =  1.0f, .h = 1.0f,
        .frame = KNIGHT_SHOOT_RIGHT_1_TEX
    };
    frame_data[KNIGHT][UP][KNIGHT_SHOOT_1] = (FrameData) {
        .x = 0.0f, .y = 0.0f, .w = 1.0f, .h = 1.0f,
        .frame = KNIGHT_SHOOT_UP_1_TEX
    };
    frame_data[KNIGHT][LEFT][KNIGHT_SHOOT_1] = (FrameData) {
        .x = 0.0f, .y = 0.0f, .w = 1.0f, .h = 1.0f,
        .frame = KNIGHT_SHOOT_LEFT_1_TEX
    };

    frame_data[KNIGHT][DOWN][KNIGHT_SHOOT_2] = (FrameData) {
        .x = 0.0f, .y = 0.0f, .w = 1.0f, .h = 1.0f,
        .frame = KNIGHT_SHOOT_DOWN_2_TEX
    };
    frame_data[KNIGHT][RIGHT][KNIGHT_SHOOT_2] = (FrameData) {
        .x = 1.5f / 8.0f, .y = 0.0f, .w = 11.0f / 8.0f, .h = 1.0f,
        .frame = KNIGHT_SHOOT_RIGHT_2_TEX
    };
    frame_data[KNIGHT][UP][KNIGHT_SHOOT_2] = (FrameData) {
        .x = 0.0f, .y = 0.0f, .w = 1.0f, .h = 1.0f,
        .frame = KNIGHT_SHOOT_UP_2_TEX
    };
    frame_data[KNIGHT][LEFT][KNIGHT_SHOOT_2] = (FrameData) {
        .x = -1.5f / 8.0f, .y = 0.0f, .w = 11.0f / 8.0f, .h = 1.0f,
        .frame = KNIGHT_SHOOT_LEFT_2_TEX
    };
}

void knight_destroy_frame_data(FrameData ***frame_data)
{
    for (i32 i = 0; i < 4; i++)
        free(frame_data[KNIGHT][i]);
    free(frame_data[KNIGHT]);
}

void knight_update_state(Entity *entity)
{
    if (entity->flag == TRUE) {
        if (entity->state != KNIGHT_SHOOT_1 && entity->state != KNIGHT_SHOOT_2) {
            entity->state = KNIGHT_SHOOT_1;
            entity->timer = 0;
            entity->face_dir = FALSE;
        }
        entity->flag = FALSE;
    } else {
        if (entity->state == KNIGHT_SHOOT_2) {
            if (entity->timer > 0.15) {
                entity->state = KNIGHT_IDLE;
                entity->timer = 0;
                entity->face_dir = TRUE;
            }
        }
    }
    
    if (vec3f_mag(entity->direction) == 0) {
        if (entity->state == KNIGHT_WALK_1 || entity->state == KNIGHT_WALK_2)
            entity->state = KNIGHT_IDLE;
    }
    else {
        if (entity->state == KNIGHT_IDLE)
            entity->state = KNIGHT_WALK_1;
    }

    switch (entity->state) {
        case KNIGHT_WALK_1:
            if (entity->timer > 0.15) {
                entity->timer = 0;
                entity->state = KNIGHT_WALK_2;
            }
            break;
        case KNIGHT_WALK_2:
            if (entity->timer > 0.15) {
                entity->timer = 0;
                entity->state = KNIGHT_WALK_1;
            }
            break;
        case KNIGHT_SHOOT_1:
            if (entity->timer > 0.15) {
                entity->timer = 0;
                entity->state = KNIGHT_SHOOT_2;
            }
            break;
        case KNIGHT_SHOOT_2:
            if (entity->timer > 0.15) {
                entity->timer = 0;
                entity->state = KNIGHT_SHOOT_1;
            }
            break;
        default:
            break;
    }
}