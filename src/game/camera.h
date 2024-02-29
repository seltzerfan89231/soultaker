#ifndef CAMERA_H
#define CAMERA_H

#include <gtype.h>
#include <gvec.h>

#define NEAR_CLIP_DISTANCE 0.1
#define FAR_CLIP_DISTANCE 10000

typedef struct Camera {
    f32 yaw, pitch, speed, sensitivity, aspect_ratio, fov;
    f32 view[16], proj[16];
    vec3f position, direction, right, up;
    u8 viewID, projID;
} Camera;

void camera_init(void);
void camera_update_view(void);
void camera_update_proj(void);

extern Camera camera;

#endif