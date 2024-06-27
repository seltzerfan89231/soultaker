#ifndef KNIGHT_H
#define KNIGHT_H

#include <stdlib.h>

inline static void knight_init(u32 ***frames)
{
    frames[KNIGHT] = malloc(4 * sizeof(u32*));
    for (i32 i = 0; i < 4; i++)
        frames[KNIGHT][i] = malloc(KNIGHT_STATES * sizeof(u32));
    frames[KNIGHT][DOWN][KNIGHT_IDLE] = KNIGHT_IDLE_DOWN_TEX;
    frames[KNIGHT][RIGHT][KNIGHT_IDLE] = KNIGHT_IDLE_RIGHT_TEX;
    frames[KNIGHT][UP][KNIGHT_IDLE] = KNIGHT_IDLE_UP_TEX;
    frames[KNIGHT][LEFT][KNIGHT_IDLE] = KNIGHT_IDLE_LEFT_TEX;
    frames[KNIGHT][DOWN][KNIGHT_SHOOT_1] = KNIGHT_SHOOT_DOWN_TEX;
    frames[KNIGHT][RIGHT][KNIGHT_SHOOT_1] = KNIGHT_SHOOT_RIGHT_TEX;
    frames[KNIGHT][UP][KNIGHT_SHOOT_1] = KNIGHT_SHOOT_UP_TEX;
    frames[KNIGHT][LEFT][KNIGHT_SHOOT_1] = KNIGHT_SHOOT_LEFT_TEX;
}

inline static void knight_destroy(u32 ***frames)
{
    for (i32 i = 0; i < 4; i++)
        free(frames[KNIGHT][i]);
    free(frames[KNIGHT]);
}

#endif