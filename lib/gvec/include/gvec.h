#ifndef GVEC_H
#define GVEC_H

#define _VEC2_STRUCT(_type) \
    typedef struct vec2##_type { \
        _type ## 32 x, y; \
    } vec2 ## _type;

#define _VEC2_ADD(_type) \
    static inline vec2##_type vec2##_type##_add(vec2##_type vec1, vec2##_type vec2) { \
        vec2##_type vec; \
        vec.x = vec1.x + vec2.x; \
        vec.y = vec1.y + vec2.y; \
        return vec; \
    }

#define _VEC2_SUB(_type) \
    static inline vec2##_type vec2##_type##_sub(vec2##_type vec1, vec2##_type vec2) { \
        vec2##_type vec; \
        vec.x = vec1.x - vec2.x; \
        vec.y = vec1.y - vec2.y; \
        return vec; \
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
    typedef struct vec3 ## _type { \
        _type ## 32 x, y, z; \
    } vec3 ## _type;

#endif