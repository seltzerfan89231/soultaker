#include "../entity.h"

#define NUM_STATES 1
#define IDLE   0

void shaitan_the_advisor_init_frame_data(FrameData ***frame_data)
{
    frame_data[SHAITAN_THE_ADVISOR] = malloc(4 * sizeof(FrameData*));
    for (i32 i = 0; i < 4; i++)
        frame_data[SHAITAN_THE_ADVISOR][i] = malloc(NUM_STATES * sizeof(FrameData));
    frame_data[SHAITAN_THE_ADVISOR][DOWN][IDLE]  = _FDdef(SHAITAN_THE_ADVISOR_CLOSED_TEX);
    frame_data[SHAITAN_THE_ADVISOR][RIGHT][IDLE] = _FDdef(SHAITAN_THE_ADVISOR_CLOSED_TEX);
    frame_data[SHAITAN_THE_ADVISOR][UP][IDLE]    = _FDdef(SHAITAN_THE_ADVISOR_CLOSED_TEX);
    frame_data[SHAITAN_THE_ADVISOR][LEFT][IDLE]  = _FDdef(SHAITAN_THE_ADVISOR_CLOSED_TEX);
}

void shaitan_the_advisor_destroy_frame_data(FrameData ***frame_data)
{
    for (i32 i = 0; i < 4; i++)
        free(frame_data[SHAITAN_THE_ADVISOR][i]);
    free(frame_data[SHAITAN_THE_ADVISOR]);
}

void shaitan_the_advisor_create(Entity *entity)
{
    
}

void shaitan_the_advisor_update(Entity *entity)
{

}

void shaitan_the_advisor_damage(Entity *entity, f32 damage)
{
    
}

void shaitan_the_advisor_die(Entity *entity)
{
    
}