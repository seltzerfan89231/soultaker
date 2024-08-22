#ifndef OBSTACLE_H
#define OBSTACLE_H

#include "../../util/array.h"
#include "../../util/type.h"
#include "../../util/vec.h"
#include "../../util/indices.h"

typedef struct {
    f32 scale, hitbox_radius;
    u32 tex;
    vec3f position;
} Obstacle;

Obstacle* obstacle_create(f32 x, f32 z);
void obstacle_destroy(Obstacle* Obstacle, u32 idx);
void destroy_all_obstacles(void);

_ARRAY_DECLARE(Obstacle, obstacle)
extern ObstacleArray global_obstacles;

#endif