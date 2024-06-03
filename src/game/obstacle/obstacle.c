#include "obstacle.h"
#include <stdlib.h>

Obstacle* obstacle_create(void)
{
    Obstacle *obstacle = malloc(sizeof(Obstacle));
    obstacle->scale = 1.0f;
    obstacle->hitbox_radius = 0.5f;
    return obstacle;
}

void obstacle_destroy(Obstacle* obstacle)
{
    free(obstacle);
}