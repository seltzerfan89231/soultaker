#include "obstacle.h"
#include <stdlib.h>

ObstacleArray obstacles;

Obstacle* obstacle_create(void)
{
    Obstacle *obstacle = malloc(sizeof(Obstacle));
    obstacle->scale = 1.0f;
    obstacle->hitbox_radius = 0.5f;
    obstacle_array_push(&obstacles, obstacle);
    return obstacle;
}

void obstacle_destroy(Obstacle* obstacle)
{
    free(obstacle);
}

_ARRAY_DEFINE(Obstacle, obstacle)