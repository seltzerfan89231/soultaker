#include "camera.h"
#include <math.h>
#define PI 3.141592653589

Camera camera;

static void identity(f32 m[16]);
static void view(f32 m[16], vec3f r, vec3f u, vec3f f, vec3f p);
static void proj(f32 m[16], f32 ar, f32 fov, f32 ncd, f32 fcd);

void camera_init(void)
{
    vec3f target;
    camera.yaw = 0;
    camera.pitch = 0;
    camera.speed = 25;
    camera.sensitivity = 0.001;
    camera.fov = PI / 4;
    identity(camera.view);
    identity(camera.proj);
    vec3f_set(&target, 0.0f, 0.0f, 0.0f);
    vec3f_set(&camera.position, 0.0f, 0.0f, 3.0f);
    vec3f_set(&camera.up, 0.0f, 1.0f, 0.0f);
    camera.direction = vec3f_normalize(vec3f_sub(target, camera.position));
    camera.right = vec3f_normalize(vec3f_cross(camera.up, camera.direction));
    camera.up = vec3f_normalize(vec3f_cross(camera.direction, camera.right));
}

void camera_update_view(void)
{
    view(camera.view, camera.right, camera.up, camera.direction, camera.position);
    glUniformMatrix4fv(camera.viewID, 1, GL_FALSE, camera.view);
}

void camera_update_proj(void)
{
    proj(camera.proj, camera.aspect_ratio, camera.fov, NEAR_CLIP_DISTANCE, FAR_CLIP_DISTANCE);
    glUniformMatrix4fv(camera.projID, 1, GL_FALSE, camera.proj);
}

/* --------------- matrix ----------------- */

void identity(f32 m[16])
{
    /* create 4x4 identity matrix */
    m[0]  = 1; m[1]  = 0; m[2]  = 0; m[3]  = 0;
    m[4]  = 0; m[5]  = 1; m[6]  = 0; m[7]  = 0;
    m[8]  = 0; m[9]  = 0; m[10] = 1; m[11] = 0;
    m[12] = 0; m[13] = 0; m[14] = 0; m[15] = 1;
}

void view(f32 m[16], vec3f r, vec3f u, vec3f f, vec3f p)
{
    /* create view matrix */
    float k1 = p.x * r.x + p.y * r.y + p.z * r.z;
    float k2 = p.x * u.x + p.y * u.y + p.z * u.z;
    float k3 = p.x * f.x + p.y * f.y + p.z * f.z;
    m[0]  = r.x; m[1]  = u.x; m[2]  = f.x; m[3]  = 0;
    m[4]  = r.y; m[5]  = u.y; m[6]  = f.y; m[7]  = 0;
    m[8]  = r.z; m[9]  = u.z; m[10] = f.z; m[11] = 0;
    m[12] = -k1; m[13] = -k2; m[14] = -k3; m[15] = 1;
}

void proj(f32 m[16], f32 ar, f32 fov, f32 ncd, f32 fcd)
{
    /* create projection matrix */
    f32 a, b, c, d;
    a = 1 / (ar * tan(fov / 2));
    b = 1 / (tan(fov / 2));
    c = (-ncd-fcd) / (ncd - fcd);
    d = (2 * fcd * ncd) / (ncd - fcd);
    m[0]  = a; m[1]  = 0; m[2]  = 0; m[3]  = 0;
    m[4]  = 0; m[5]  = b; m[6]  = 0; m[7]  = 0;
    m[8]  = 0; m[9]  = 0; m[10] = c; m[11] = 1;
    m[12] = 0; m[13] = 0; m[14] = d; m[15] = 0;
}

/* ---------------------------------------- */