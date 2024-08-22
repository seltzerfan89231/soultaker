#include "obstacle.h"
#include <stdlib.h>
#include <assert.h>
#include "../tilemap/tilemap.h"

ObstacleArray global_obstacles;

Obstacle* obstacle_create(f32 x, f32 z)
{
    Obstacle *obstacle = malloc(sizeof(Obstacle));
    obstacle->position = vec3f_create(x, 0, z);
    obstacle->scale = 1.0f;
    obstacle->tex = ROCK_TEX;
    obstacle->hitbox_radius = 0.5f;
    obstacle_array_push(&global_obstacles, obstacle);
    tilemap_insert_obstacle(obstacle);
    return obstacle;
}

void obstacle_destroy(Obstacle* obstacle, u32 idx)
{
    assert(obstacle == global_obstacles.buffer[idx]);
    obstacle_array_cut(&global_obstacles, idx);
    free(obstacle);
}

void destroy_all_obstacles(void)
{
    for (i32 i = 0; i < global_obstacles.length; i++)
        free(global_obstacles.buffer[i]);
    obstacle_array_destroy(&global_obstacles);
}

_ARRAY_DEFINE(Obstacle, obstacle)