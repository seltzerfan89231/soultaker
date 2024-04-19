#include "camera.h"

Camera camera;

static void camera_update(void)
{
    camera.facing.x = cos(camera.yaw) * cos(-camera.pitch);
    camera.facing.y = sin(-camera.pitch);
    camera.facing.z = sin(camera.yaw) * cos(-camera.pitch);
    camera.position = vec3f_add(camera.target, vec3f_scale(-DEFAULT_DISTANCE, camera.facing));
    camera.right = vec3f_normalize(vec3f_cross(Y_AXIS, camera.facing));
    camera.up = vec3f_cross(camera.facing, camera.right);
    camera_update_view();
}

void camera_init(void)
{
    camera.yaw = DEFAULT_YAW;
    camera.pitch = DEFAULT_PITCH;
    camera.fov = DEFAULT_FOV;
    camera.rotate_speed = DEFAULT_ROTATE_SPEED;
    camera.move_speed = DEFAULT_MOVE_SPEED;
    camera.zoom = DEFAULT_ZOOM;
    camera.target = ORIGIN;
    camera_update();
    camera_update_proj();
}

void camera_rotate(i32 mag, f32 dt)
{
    camera.yaw += mag * dt * camera.rotate_speed;
    camera_update();
}

void camera_tilt(i32 mag, f32 dt)
{
    camera.pitch += mag * dt;
    if (camera.pitch <= MIN_PITCH)
        camera.pitch = MIN_PITCH;
    if (camera.pitch >= MAX_PITCH)
        camera.pitch = MAX_PITCH;
    camera_update();
}

void camera_zoom(i32 mag, f32 dt)
{
    camera.zoom += mag * dt;
    if (camera.zoom < MIN_ZOOM)
        camera.zoom = MIN_ZOOM;
    if (camera.zoom > MAX_ZOOM)
        camera.zoom = MAX_ZOOM;
    camera_update_proj();
}

vec3f camera_move(vec2i dir, f32 dt)
{
    vec3f vec, offset;
    vec2f v1, v2;
    v1 = vec2f_normalize(vec2f_create(camera.facing.x, camera.facing.z));
    v2 = vec2f_create(camera.right.x, camera.right.z);
    vec = vec3f_normalize(vec3f_create(v1.x * dir.x + v2.x * dir.y, 0, v1.y * dir.x + v2.y * dir.y));
    offset = vec3f_scale(camera.move_speed * dt, vec);
    camera.target = vec3f_add(camera.target, offset);
    camera.position = vec3f_add(camera.position, offset);
    camera_update_view();
    return camera.target;
}

void camera_aspect_ratio(f32 ar)
{
    camera.aspect_ratio = ar;
    camera_update_proj();
}

void camera_update_view(void)
{
    view(camera.view, camera.right, camera.up, camera.facing, camera.position);
}

void camera_update_proj(void)
{
    ortho(camera.proj, camera.aspect_ratio, camera.zoom);
}