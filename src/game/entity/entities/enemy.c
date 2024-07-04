#include "../entity.h"
#include <glfw.h>

#define NUM_STATES 1
#define IDLE   0
#define WALK_1 2

void enemy_init_frame_data(FrameData ***frame_data)
{
    frame_data[ENEMY] = malloc(4 * sizeof(FrameData*));
    for (i32 i = 0; i < 4; i++)
        frame_data[ENEMY][i] = malloc(NUM_STATES * sizeof(FrameData));
    frame_data[ENEMY][DOWN][IDLE]  = _FDdef(KNIGHT_IDLE_DOWN_TEX);
    frame_data[ENEMY][RIGHT][IDLE] = _FDdef(KNIGHT_IDLE_RIGHT_TEX);
    frame_data[ENEMY][UP][IDLE]    = _FDdef(KNIGHT_IDLE_UP_TEX);
    frame_data[ENEMY][LEFT][IDLE]  = _FDdef(KNIGHT_IDLE_LEFT_TEX);
}

void enemy_destroy_frame_data(FrameData ***frame_data)
{
    for (i32 i = 0; i < 4; i++)
        free(frame_data[ENEMY][i]);
    free(frame_data[ENEMY]);
}

void enemy_update(Entity *entity)
{
    static f32 cooldown;
    if (glfwGetTime() - cooldown >= 0.05) {
        cooldown = glfwGetTime();
        for (i32 i = 0; i < 1; i++) {
            Projectile* proj = projectile_create(ONE, 0);
            proj->position = entity->position;
            proj->rotation = i * 0.8 + sin(glfwGetTime());
            proj->direction = vec3f_create(cos(proj->rotation), 0.0f, sin(proj->rotation));
            proj->scale = 1.0f;
            proj->lifetime = 3.0f;
            proj->hitbox_radius = (proj->scale - 0.4) / 2;
            proj->position.y = 0.5f;
            projectile_array_push(projectiles_ptr, proj);
        }
    }
}