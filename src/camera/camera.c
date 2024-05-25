#include "camera.h"

Camera camera;

static void update_view_matrix(void) { 
    view(camera.view, camera.right, camera.up, camera.facing, camera.position); 
}

static void update_proj_matrix(f32 ar) { 
    ortho(camera.proj, ar, camera.zoom); 
}

static void update_orientation_vectors(void)
{
    camera.facing.x = cos(camera.yaw) * cos(-camera.pitch);
    camera.facing.y = sin(-camera.pitch);
    camera.facing.z = sin(camera.yaw) * cos(-camera.pitch);
    camera.position = vec3f_add(camera.target, vec3f_scale(-DEFAULT_DISTANCE, camera.facing));
    camera.right = vec3f_normalize(vec3f_cross(Y_AXIS, camera.facing));
    camera.up = vec3f_cross(camera.facing, camera.right);
}

void camera_init(f32 ar)
{
    camera.yaw = DEFAULT_YAW;
    camera.pitch = DEFAULT_PITCH;
    camera.fov = DEFAULT_FOV;
    camera.rotate_speed = DEFAULT_ROTATE_SPEED;
    camera.zoom = DEFAULT_ZOOM;
    camera.target = vec3f_create(0.0f, 0.0f, 0.0f);
    update_orientation_vectors();
    update_view_matrix();
    update_proj_matrix(ar);
}

void camera_rotate(i32 mag, f32 dt)
{
    camera.yaw += mag * dt * camera.rotate_speed;
    if (camera.yaw > 2 * PI)
        camera.yaw -= 2 * PI;
    if (camera.yaw < 0)
        camera.yaw += 2 * PI;
    update_orientation_vectors();
    update_view_matrix();
}

void camera_tilt(i32 mag, f32 dt)
{
    camera.pitch += mag * dt;
    if (camera.pitch <= MIN_PITCH)
        camera.pitch = MIN_PITCH;
    if (camera.pitch >= MAX_PITCH)
        camera.pitch = MAX_PITCH;
    update_orientation_vectors();
    update_view_matrix();
}

void camera_zoom(i32 mag, f32 dt, f32 ar)
{
    camera.zoom += mag * dt * 5;
    if (camera.zoom < MIN_ZOOM)
        camera.zoom = MIN_ZOOM;
    if (camera.zoom > MAX_ZOOM)
        camera.zoom = MAX_ZOOM;
    update_proj_matrix(ar);
}

void camera_set_target(vec3f target)
{
    camera.target = target;
    camera.position = vec3f_add(camera.target, vec3f_scale(-DEFAULT_DISTANCE, camera.facing));
    update_view_matrix();
}

vec3f camera_get_direction(vec2i dir)
{
    vec3f vec, offset;
    vec2f v1, v2;
    v1 = vec2f_normalize(vec2f_create(camera.facing.x, camera.facing.z));
    v2 = vec2f_create(camera.right.x, camera.right.z);
    vec = vec3f_normalize(vec3f_create(v1.x * dir.x + v2.x * dir.y, 0, v1.y * dir.x + v2.y * dir.y));
    return vec;
}


