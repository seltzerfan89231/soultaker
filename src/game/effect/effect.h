#ifndef EFFECT_H
#define EFFECT_H

#include "../../util/array.h"
#include "../../util/type.h"
#include "../../util/vec.h"
#include "../../util/constants.h"

typedef struct {
    vec3f position;
    u32 id;
    f32 duration, radius;
} AreaEffect;

#endif