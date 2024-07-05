#ifndef PARSTACLE_H
#define PARSTACLE_H

#include "../../util/array.h"
#include "../../util/type.h"
#include "../../util/vec.h"

typedef struct {
    f32 scale;
    vec3f position;
} Parstacle;

Parstacle* parstacle_create(void);
void parstacle_destroy(Parstacle* parstacle);

_ARRAY_DECLARE(Parstacle, parstacle)
extern ParstacleArray parstacles;

#endif