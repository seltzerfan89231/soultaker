#ifndef CAMERA_H
#define CAMERA_H

#include <math.h>
#include "../util/type.h"
#include "../util/vec.h"
#include "../util/mat.h"
#include "../util/constants.h"

#define ORIGIN vec3f_create(0.0f, 0.0f, 0.0f);
#define Y_AXIS vec3f_create(0.0f, 1.0f, 0.0f)
#define DEFAULT_DISTANCE 100
#define DEFAULT_PITCH PI / 3
#define DEFAULT_ROTATE_SPEED 3
#define DEFAULT_TILT_SPEED 3
#define DEFAULT_MOVE_SPEED 8
#define DEFAULT_YAW PI / 2
#define DEFAULT_FOV PI/4
#define DEFAULT_ZOOM 5
#define MIN_PITCH 0.3
#define MAX_PITCH 1.3
#define MIN_ZOOM 1
#define MAX_ZOOM 10

typedef struct Camera {
    f32 yaw, pitch, aspect_ratio, fov, rotate_speed, move_speed, zoom;
    f32 view[16], proj[16];
    vec3f target, position, facing, right, up;
} Camera;

extern Camera camera;

void camera_init(void);
void camera_rotate(i32 mag, f32 dt);
void camera_tilt(i32 mag, f32 dt);
void camera_zoom(i32 mag, f32 dt);
vec3f camera_move(vec2i dir, f32 dt);
void camera_aspect_ratio(f32 ar);
void camera_update_view(void);
void camera_update_proj(void);

#endif