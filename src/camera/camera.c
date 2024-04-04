#include "camera.h"
#include "mat.h"
#include <math.h>

Camera camera;

static void camera_update(void)
{
    camera.facing.x = cos(camera.yaw) * cos(-camera.pitch);
    camera.facing.y = sin(-camera.pitch);
    camera.facing.z = sin(camera.yaw) * cos(-camera.pitch);
    camera.position = vec3f_add(camera.target, vec3f_scale(-DISTANCE, camera.facing));
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
    camera.target = vec3f_create(0.0f, 0.0f, 0.0f);
    camera_update();
}

f32 camera_rotate(i32 mag, f32 dt)
{
    camera.yaw += mag * dt * camera.rotate_speed;
    camera_update();
    return camera.yaw;
}

f32 camera_tilt(i32 mag, f32 dt)
{
    camera.pitch += mag * dt;
    if (camera.pitch <= 0.3)
        camera.pitch = 0.3;
    if (camera.pitch >= PI / 2 - 0.3)
        camera.pitch = PI / 2 - 0.3;
    camera_update();
    return camera.pitch;
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

void camera_update_view(void)
{
    view(camera.view, camera.right, camera.up, camera.facing, camera.position);
    glUniformMatrix4fv(camera.viewID, 1, GL_FALSE, camera.view);
}

void camera_update_proj(void)
{
    ortho(camera.proj, camera.aspect_ratio, camera.zoom);
    glUniformMatrix4fv(camera.projID, 1, GL_FALSE, camera.proj);
}