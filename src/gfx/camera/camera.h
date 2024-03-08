#ifndef CAMERA_H
#define CAMERA_H

#include <gtype.h>
#include <gvec.h>

#define Y_AXIS vec3f_create(0.0f, 1.0f, 0.0f)
#define DISTANCE 12
#define PI 3.141592653589

#define DEFAULT_PITCH - PI / 3
#define DEFAULT_ROTATE_SPEED 1
#define DEFAULT_MOVE_SPEED 8
#define DEFAULT_YAW 0
#define DEFAULT_FOV PI/4

typedef struct Camera {
    f32 yaw, pitch, aspect_ratio, fov, rotate_speed, move_speed;
    f32 view[16], proj[16];
    vec3f target, position, facing, right, up;
    u8 viewID, projID;
} Camera;

extern Camera camera;

void camera_init(void);
void camera_rotate(i32 dir, f32 dt);
void camera_move(vec2i dir, f32 dt);
void camera_update_view(void);
void camera_update_proj(void);

#endif