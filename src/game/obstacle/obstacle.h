#ifndef OBSTACLE_H
#define OBSTACLE_H

#include "../../util/array.h"
#include "../../util/type.h"
#include "../../util/vec.h"

typedef struct {
    f32 scale, hitbox_radius;
    vec3f position;
} Obstacle;

Obstacle* obstacle_create(void);
void obstacle_destroy(Obstacle* Obstacle);

_ARRAY_DECLARE(Obstacle, obstacle)
extern ObstacleArray obstacles;

#endif