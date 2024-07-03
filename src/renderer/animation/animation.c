#include "animation.h"
#include <stdlib.h>

void animation_init_entities(Animation *animation)
{
    animation->frame_data = malloc(MAX_ENTITY_ID * sizeof(FrameData**));
    FrameData ***frame_data = animation->frame_data;
    /* ---------------- */
    frame_data[KNIGHT] = malloc(4 * sizeof(FrameData*));
    for (i32 i = 0; i < 4; i++)
        frame_data[KNIGHT][i] = malloc(KNIGHT_STATES * sizeof(FrameData));
    frame_data[KNIGHT][DOWN][KNIGHT_IDLE] = (FrameData) {
        .x = 0.0f, .y = 0.0f, .w = 1.0f, .h = 1.0f,
        .frame = KNIGHT_IDLE_DOWN_TEX
    };
    frame_data[KNIGHT][RIGHT][KNIGHT_IDLE] = (FrameData) {
        .x = 0.0f, .y = 0.0f, .w = 1.0f, .h = 1.0f,
        .frame = KNIGHT_IDLE_RIGHT_TEX
    };
    frame_data[KNIGHT][UP][KNIGHT_IDLE] = (FrameData) {
        .x = 0.0f, .y = 0.0f, .w = 1.0f, .h = 1.0f,
        .frame = KNIGHT_IDLE_UP_TEX
    };
    frame_data[KNIGHT][LEFT][KNIGHT_IDLE] = (FrameData) {
        .x = 0.0f, .y = 0.0f, .w = 1.0f, .h = 1.0f,
        .frame = KNIGHT_IDLE_LEFT_TEX
    };

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

    /* ---------------- */
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

void animation_destroy_entities(Animation *animation)
{
    for (i32 i = 0; i < 4; i++)
        free(animation->frame_data[KNIGHT][i]);
    free(animation->frame_data[KNIGHT]);

    for (i32 i = 0; i < 4; i++)
        free(animation->frame_data[ENEMY][i]);
    free(animation->frame_data[ENEMY]);

    free(animation->frame_data);
}