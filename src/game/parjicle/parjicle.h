#ifndef PARJICLE_H
#define PARJICLE_H

#include "../../util/array.h"
#include "../../util/type.h"
#include "../../util/vec.h"

typedef struct {
    f32 speed, scale, lifetime, rotation;
    vec3f position, direction;
    struct {
        f32 r, g, b;
    } color;
} Parjicle;

Parjicle* parjicle_create(f32 rotation);
void parjicle_update(Parjicle *parjicle, f32 dt);
void parjicle_destroy(Parjicle *parj, u32 idx);
void destroy_all_parjicles(void);

_ARRAY_DECLARE(Parjicle, parjicle)
extern ParjicleArray global_parjicles;

#endif