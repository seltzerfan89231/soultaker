#include "../entity.h"

void enemy_init_frame_data(FrameData ***frame_data)
{
    frame_data[ENEMY] = malloc(4 * sizeof(FrameData*));
    for (i32 i = 0; i < 4; i++)
        frame_data[ENEMY][i] = malloc(ENEMY_STATES * sizeof(FrameData));
    frame_data[ENEMY][DOWN][ENEMY_IDLE] = (FrameData) {
        .x = 0.0f, .y = 0.0f, .w = 1.0f, .h = 1.0f,
        .frame = KNIGHT_IDLE_DOWN_TEX
    };
    frame_data[ENEMY][RIGHT][ENEMY_IDLE] = (FrameData) {
        .x = 0.0f, .y = 0.0f, .w = 1.0f, .h = 1.0f,
        .frame = KNIGHT_IDLE_RIGHT_TEX
    };
    frame_data[ENEMY][UP][ENEMY_IDLE] = (FrameData) {
        .x = 0.0f, .y = 0.0f, .w = 1.0f, .h = 1.0f,
        .frame = KNIGHT_IDLE_UP_TEX
    };
    frame_data[ENEMY][LEFT][ENEMY_IDLE] = (FrameData) {
        .x = 0.0f, .y = 0.0f, .w = 1.0f, .h = 1.0f,
        .frame = KNIGHT_IDLE_LEFT_TEX
    };
}

void enemy_destroy_frame_data(FrameData ***frame_data)
{
    for (i32 i = 0; i < 4; i++)
        free(frame_data[ENEMY][i]);
    free(frame_data[ENEMY]);
}