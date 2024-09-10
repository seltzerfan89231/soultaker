#include "../entity.h"

extern f32 game_time;

#define NUM_STATES 1
#define IDLE   0

void training_dummy_init_frame_data(FrameData ***frame_data)
{
    frame_data[TRAINING_DUMMY] = malloc(4 * sizeof(FrameData*));
    for (i32 i = 0; i < 4; i++)
        frame_data[TRAINING_DUMMY][i] = malloc(NUM_STATES * sizeof(FrameData));
    frame_data[TRAINING_DUMMY][DOWN][IDLE]  = _FDdef(TRAINING_DUMMY_TEX);
    frame_data[TRAINING_DUMMY][RIGHT][IDLE] = _FDdef(TRAINING_DUMMY_TEX);
    frame_data[TRAINING_DUMMY][UP][IDLE]    = _FDdef(TRAINING_DUMMY_TEX);
    frame_data[TRAINING_DUMMY][LEFT][IDLE]  = _FDdef(TRAINING_DUMMY_TEX);
}

void training_dummy_destroy_frame_data(FrameData ***frame_data)
{
    for (i32 i = 0; i < 4; i++)
        free(frame_data[TRAINING_DUMMY][i]);
    free(frame_data[TRAINING_DUMMY]);
}

void training_dummy_create(Entity *entity)
{
    entity->health = 20;
    entity->max_health = 20;
}

void training_dummy_update(Entity *entity, f32 dt)
{
    if (entity->timer > 2) {
        entity->timer = 0;
        entity->health = entity->max_health;
    }
}

void training_dummy_damage(Entity *entity, f32 damage)
{
    entity->health -= damage;
    if (entity->health < 1)
        entity->health = 1;
}

void training_dummy_die(Entity *entity)
{

}