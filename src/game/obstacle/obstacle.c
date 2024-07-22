#include "obstacle.h"
#include <stdlib.h>
#include <assert.h>

ObstacleArray obstacles;

Obstacle* obstacle_create(void)
{
    Obstacle *obstacle = malloc(sizeof(Obstacle));
    obstacle->scale = 1.0f;
    obstacle->tex = ROCK_TEX;
    obstacle->hitbox_radius = 0.5f;
    obstacle_array_push(&obstacles, obstacle);
    return obstacle;
}

void obstacle_destroy(Obstacle* obstacle, u32 idx)
{
    assert(obstacle == obstacles.buffer[idx]);
    obstacle_array_cut(&obstacles, idx);
    free(obstacle);
}

_ARRAY_DEFINE(Obstacle, obstacle)