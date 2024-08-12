#include "../entity.h"
#include "../../player/player.h"

#define NUM_STATES 1
#define IDLE   0

void slime_init_frame_data(FrameData ***frame_data)
{
    frame_data[SLIME] = malloc(4 * sizeof(FrameData*));
    for (i32 i = 0; i < 4; i++)
        frame_data[SLIME][i] = malloc(NUM_STATES * sizeof(FrameData));
    frame_data[SLIME][DOWN][IDLE]  = _FDdef(SLIME_TEX);
    frame_data[SLIME][RIGHT][IDLE] = _FDdef(SLIME_TEX);
    frame_data[SLIME][UP][IDLE]    = _FDdef(SLIME_TEX);
    frame_data[SLIME][LEFT][IDLE]  = _FDdef(SLIME_TEX);
}

void slime_destroy_frame_data(FrameData ***frame_data)
{
    for (i32 i = 0; i < 4; i++)
        free(frame_data[SLIME][i]);
    free(frame_data[SLIME]);
}

void slime_update(Entity *entity)
{
    if (player.entity == NULL) {
        entity->direction = vec3f_create(0, 0, 0);
        return;
    }
    vec3f target, offset;
    target = player.entity->position;
    offset = vec3f_sub(target, entity->position);
    if (vec3f_mag(offset) < 10) {
        entity->direction = vec3f_normalize(offset);
        if (entity->timer >= 0.5) {
            entity->timer = 0;
            Projectile* proj = projectile_create(SWORD, FALSE);
            proj->position = entity->position;
            proj->rotation = atan(entity->direction.z / entity->direction.x) + (entity->direction.x > 0 ? 0 : PI);
            proj->direction = entity->direction;
            proj->scale = 1.0f;
            proj->lifetime = 3.0f;
            proj->hitbox_radius = (proj->scale - 0.4) / 2;
            proj->position.y = 0.5f;
        }
    }
    else
        entity->direction = vec3f_create(0, 0, 0);
}

void slime_die(Entity *entity)
{}