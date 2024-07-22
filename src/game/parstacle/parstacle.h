#ifndef PARSTACLE_H
#define PARSTACLE_H

#include "../../util/array.h"
#include "../../util/type.h"
#include "../../util/vec.h"
#include "../../util/indices.h"

typedef struct {
    f32 scale;
    u32 tex;
    vec3f position;
} Parstacle;

Parstacle* parstacle_create(void);
void parstacle_destroy(Parstacle* parstacle, u32 idx);

_ARRAY_DECLARE(Parstacle, parstacle)
extern ParstacleArray parstacles;

#endif