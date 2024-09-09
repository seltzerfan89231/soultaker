#include "../entity.h"
#include "../../projectile/projectile.h"

#define NUM_STATES 1
#define IDLE   0

#define NUM_PHASES 3
#define INVISIBLE  0
#define GROW       1
#define ATTACK_1   2

static void attack_1(Entity* entity)
{
    i32 safe_spot = rand() % 2;
    for (i32 i = 0; i < 12; i++) {
        if (safe_spot && (i == 0 || i == 6))
            continue;
        if (!safe_spot && (i == 3 || i == 9))
            continue;
        f32 theta = 2.0 * i * PI / 12;
        Projectile* proj = projectile_create(SHAITAN_FIRESTORM_PROJ, FALSE, FALSE);
        proj->tex = SHAITAN_FIRESTORM_TEX;
        proj->position = entity->position;
        proj->position.y = 0.5;
        proj->direction = vec3f_create(cos(theta), 0.0, sin(theta));
    }
}

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
    entity->scale = 3;
    entity->phase = ATTACK_1;
    entity->invisible = FALSE;
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
                else
                    entity->phase = ATTACK_1;
                entity->timer2 = 0.5;
            }
            break;
        case ATTACK_1:
            if (entity->timer2 < 0) {
                attack_1(entity);
                entity->timer2 = 1.5;
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