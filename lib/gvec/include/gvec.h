#ifndef GVEC_H
#define GVEC_H

#include <math.h>

#define _VEC2_STRUCT(_type) \
    typedef struct vec2##_type { \
        _type##32 x, y; \
    } vec2##_type;

#define _VEC2_ADD(_type) \
    static inline vec2##_type vec2##_type##_add(vec2##_type vec1, vec2##_type vec2) { \
        vec2##_type ret; \
        ret.x = vec1.x + vec2.x; \
        ret.y = vec1.y + vec2.y; \
        return ret; \
    }

#define _VEC2_SUB(_type) \
    static inline vec2##_type vec2##_type##_sub(vec2##_type vec1, vec2##_type vec2) { \
        vec2##_type ret; \
        ret.x = vec1.x - vec2.x; \
        ret.y = vec1.y - vec2.y; \
        return ret; \
    }

_VEC2_STRUCT(u)
_VEC2_STRUCT(f)
_VEC2_STRUCT(s)

_VEC2_ADD(u)
_VEC2_ADD(f)
_VEC2_ADD(s)

_VEC2_SUB(u)
_VEC2_SUB(f)
_VEC2_SUB(s)

#define _VEC3_STRUCT(_type) \
    typedef struct vec3##_type { \
        _type##32 x, y, z; \
    } vec3##_type;

#define _VEC3_CREATE(_type) \
    static inline vec3##_type vec3##_type##_create(_type##32 x, _type##32 y, _type##32 z) { \
        vec3##_type ret; \
        ret.x = x; \
        ret.y = y; \
        ret.z = z; \
        return ret; \
    }

#define _VEC3_SUB(_type) \
    static inline vec3##_type vec3##_type##_sub(vec3##_type vec1, vec3##_type vec2) { \
        vec3##_type ret; \
        ret.x = vec1.x - vec2.x; \
        ret.y = vec1.y - vec2.y; \
        ret.z = vec1.z - vec2.z; \
        return ret; \
    }

#define _VEC3_SCALE(_type) \
    static inline vec3##_type vec3##_type##_scale(_type##32 s, vec3##_type vec) { \
        vec3##_type ret; \
        ret.x = vec.x * s; \
        ret.y = vec.y * s; \
        ret.z = vec.z * s; \
        return ret; \
    }

#define _VEC3_CROSS(_type) \
    static inline vec3##_type vec3##_type##_cross(const vec3##_type vec1, const vec3##_type vec2) { \
        vec3##_type ret; \
        ret.x = vec1.y * vec2.z - vec1.z * vec2.y; \
        ret.y = vec1.z * vec2.x - vec1.x * vec2.z; \
        ret.z = vec1.x * vec2.y - vec1.y * vec2.x; \
        return ret; \
    }

#define _VEC3_NORMALIZE(_type) \
    static inline vec3##_type vec3##_type##_normalize(vec3##_type vec) { \
        f32 mag = sqrt(vec.x*vec.x + vec.y*vec.y + vec.z*vec.z); \
        if (mag == 0) \
            vec.x = vec.y = vec.z = 0; \
        else { \
            vec.x /= mag; \
            vec.y /= mag; \
            vec.z /= mag; \
        } \
        return vec; \
    }

_VEC3_STRUCT(u)
_VEC3_STRUCT(f)
_VEC3_STRUCT(s)

_VEC3_CREATE(u)
_VEC3_CREATE(f)
_VEC3_CREATE(s)

_VEC3_SUB(u)
_VEC3_SUB(f)
_VEC3_SUB(s)

_VEC3_SCALE(u)
_VEC3_SCALE(f)
_VEC3_SCALE(s)

_VEC3_CROSS(u)
_VEC3_CROSS(f)
_VEC3_CROSS(s)

_VEC3_NORMALIZE(u)
_VEC3_NORMALIZE(f)
_VEC3_NORMALIZE(s)

#endif