#include "animation.h"
#include <stdlib.h>
#include <stdio.h>

Animation animation;

void animation_init(void)
{
    animation.frames = malloc(MAX_ENTITY_ID * sizeof(u32**));
    animation.frames[KNIGHT] = malloc(4 * sizeof(u32*));
    for (i32 i = 0; i < 4; i++)
        animation.frames[KNIGHT][i] = malloc(KNIGHT_FRAMES * sizeof(u32));
    animation.frames[KNIGHT][DOWN][KNIGHT_IDLE] = KNIGHT_DOWN_TEX;
    animation.frames[KNIGHT][RIGHT][KNIGHT_IDLE] = KNIGHT_RIGHT_TEX;
    animation.frames[KNIGHT][UP][KNIGHT_IDLE] = KNIGHT_UP_TEX;
    animation.frames[KNIGHT][LEFT][KNIGHT_IDLE] = KNIGHT_LEFT_TEX;
    animation.frames[KNIGHT][DOWN][KNIGHT_SHOOT] = KNIGHT_SHOOT_DOWN_TEX;
    animation.frames[KNIGHT][RIGHT][KNIGHT_SHOOT] = KNIGHT_SHOOT_RIGHT_TEX;
    animation.frames[KNIGHT][UP][KNIGHT_SHOOT] = KNIGHT_SHOOT_UP_TEX;
    animation.frames[KNIGHT][LEFT][KNIGHT_SHOOT] = KNIGHT_SHOOT_LEFT_TEX;
    printf("%p\n", animation.frames[KNIGHT][LEFT]);
}

void animation_destroy(void)
{

}