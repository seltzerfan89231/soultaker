#ifndef CAMERA_H
#define CAMERA_H

#include <gtype.h>
#include <gvec.h>

#define NEAR_CLIP_DISTANCE 0.1
#define FAR_CLIP_DISTANCE 10000
#define ORIGIN vec3f_create(0.0f, 0.0f, 0.0f)
#define Y_AXIS vec3f_create(0.0f, 1.0f, 0.0f)
#define PI 3.141592653589

#define DEFAULT_PITCH -PI/4
#define DEFAULT_DISTANCE 8
#define DEFAULT_YAW 0
#define DEFAULT_SPEED 25
#define DEFAULT_FOV PI/4
#define DEFAULT_SENSITIVITY 0.001

typedef struct Camera {
    f32 yaw, pitch, speed, sensitivity, aspect_ratio, fov;
    f32 view[16], proj[16];
    vec3f target, position, facing, right, up;
    u8 viewID, projID;
} Camera;

void camera_init(void);
void camera_rotate(f32 offset);
void camera_update_view(void);
void camera_update_proj(void);

extern Camera camera;

#endif