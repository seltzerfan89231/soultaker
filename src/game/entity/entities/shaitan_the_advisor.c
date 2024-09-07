#include "../entity.h"

#define NUM_STATES 1
#define IDLE   0

#define NUM_PHASES 2
#define INVISIBLE 0
#define GROW 1

void shaitan_the_advisor_init_frame_data(FrameData ***frame_data)
{
    frame_data[SHAITAN_THE_ADVISOR] = malloc(4 * sizeof(FrameData*));
    for (i32 i = 0; i < 4; i++)
        frame_data[SHAITAN_THE_ADVISOR][i] = malloc(NUM_STATES * sizeof(FrameData));
    frame_data[SHAITAN_THE_ADVISOR][DOWN][IDLE]  = _FDdef(SHAITAN_THE_ADVISOR_OPEN_TEX);
    frame_data[SHAITAN_THE_ADVISOR][RIGHT][IDLE] = _FDdef(SHAITAN_THE_ADVISOR_OPEN_TEX);
    frame_data[SHAITAN_THE_ADVISOR][UP][IDLE]    = _FDdef(SHAITAN_THE_ADVISOR_OPEN_TEX);
    frame_data[SHAITAN_THE_ADVISOR][LEFT][IDLE]  = _FDdef(SHAITAN_THE_ADVISOR_OPEN_TEX);
}

void shaitan_the_advisor_destroy_frame_data(FrameData ***frame_data)
{
    for (i32 i = 0; i < 4; i++)
        free(frame_data[SHAITAN_THE_ADVISOR][i]);
    free(frame_data[SHAITAN_THE_ADVISOR]);
}

void shaitan_the_advisor_create(Entity *entity)
{
    entity->scale = 0;
    entity->phase = INVISIBLE;
    entity->invisible = TRUE;
    entity->timer2 = 1.5;
}

void shaitan_the_advisor_update(Entity *entity)
{
    switch (entity->phase) {
        case INVISIBLE:
            if (entity->timer2 < 0) {
                entity->phase = GROW;
                entity->invisible = FALSE;
                entity->timer2 = 0.5;
            }
            break;
        case GROW:
            if (entity->timer2 < 0) {
                if (entity->scale < 3)
                    entity->scale += 0.5;
                entity->timer2 = 0.5;
            }
            break;
    }
}

void shaitan_the_advisor_damage(Entity *entity, f32 damage)
{
    entity->health -= damage;
    if (entity->health < 0)
        entity->health = 0;
}

void shaitan_the_advisor_die(Entity *entity)
{
    
}