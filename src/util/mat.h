#ifndef MAT_H
#define MAT_H

#include <math.h>
#include "vec.h"
#include "type.h"

#define NEAR_CLIP_DISTANCE 0.1f
#define FAR_CLIP_DISTANCE 1000.0f

inline static void view(f32 m[16], vec3f r, vec3f u, vec3f f, vec3f p)
{
    f32 k1 = p.x * r.x + p.y * r.y + p.z * r.z;
    f32 k2 = p.x * u.x + p.y * u.y + p.z * u.z;
    f32 k3 = p.x * f.x + p.y * f.y + p.z * f.z;
    m[0]  = r.x; m[1]  = u.x; m[2]  = f.x; m[3]  = 0.0f;
    m[4]  = r.y; m[5]  = u.y; m[6]  = f.y; m[7]  = 0.0f;
    m[8]  = r.z; m[9]  = u.z; m[10] = f.z; m[11] = 0.0f;
    m[12] = -k1; m[13] = -k2; m[14] = -k3; m[15] = 1.0f;
}

inline static void ortho(f32 m[16], f32 ar, f32 zoom)
{
    f32 r, l, t, b, f, n;
    b = -(t = zoom);
    l = -(r = ar * zoom);
    f = FAR_CLIP_DISTANCE;
    n = NEAR_CLIP_DISTANCE;
    f32 val1, val2, val3, val4, val5, val6;
    val1 = 2 / (r - l);
    val2 = 2 / (t - b);
    val3 = 2 / (f - n);
    val4 = -(r + l) / (r - l);
    val5 = -(t + b) / (t - b);
    val6 = -(f + n) / (f - n);
    m[0]  = val1; m[1]  = 0.0f; m[2]  = 0.0f; m[3]  = 0.0f;
    m[4]  = 0.0f; m[5]  = val2; m[6]  = 0.0f; m[7]  = 0.0f;
    m[8]  = 0.0f; m[9]  = 0.0f; m[10] = val3; m[11] = 0.0f;
    m[12] = val4; m[13] = val5; m[14] = val6; m[15] = 1.0f;
}

#endif