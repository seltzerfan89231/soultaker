#include "obstacle.h"
#include <stdlib.h>
#include <assert.h>
#include "../tilemap/tilemap.h"

ObstacleArray obstacles;

Obstacle* obstacle_create(f32 x, f32 z)
{
    Obstacle *obstacle = malloc(sizeof(Obstacle));
    obstacle->position = vec3f_create(x, 0, z);
    obstacle->scale = 1.0f;
    obstacle->tex = ROCK_TEX;
    obstacle->hitbox_radius = 0.5f;
    obstacle_array_push(&obstacles, obstacle);
    tilemap_insert_obstacle(obstacle);
    return obstacle;
}

void obstacle_destroy(Obstacle* obstacle, u32 idx)
{
    assert(obstacle == obstacles.buffer[idx]);
    obstacle_array_cut(&obstacles, idx);
    free(obstacle);
}

void destroy_all_obstacles(void)
{
    for (i32 i = 0; i < obstacles.length; i++)
        free(obstacles.buffer[i]);
    obstacle_array_destroy(&obstacles);
}

_ARRAY_DEFINE(Obstacle, obstacle)