#ifndef OBSTACLE_H
#define OBSTACLE_H

#include "../../util/type.h"
#include "../../util/vec.h"
#include "../../util/constants.h"

typedef struct {
    f32 scale, hitbox_radius;
    vec3f position;
} Obstacle;

Obstacle* obstacle_create(void);
void obstacle_destroy(Obstacle* Obstacle);

#endif