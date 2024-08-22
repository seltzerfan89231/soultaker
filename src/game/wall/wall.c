#include "wall.h"
#include "../tilemap/tilemap.h"
#include <stdlib.h>
#include <assert.h>

WallArray global_walls;

Wall* wall_create(u32 id, f32 x, f32 z, f32 height)
{
    Wall* wall = malloc(sizeof(Wall));
    wall->id = id;
    wall->position.x = x;
    wall->position.z = z;
    wall->height = height;
    wall->top_tex = WALL_TOP_TEX;
    wall->side_tex = WALL_SIDE_TEX;
    wall_array_push(&global_walls, wall);
    tilemap_insert_wall(wall);
    return wall;
}

void wall_destroy(Wall* wall, u32 idx)
{
    assert(wall == global_walls.buffer[idx]);
    wall_array_cut(&global_walls, idx);
    free(wall);
}

void destroy_all_walls(void)
{
    for (i32 i = 0; i < global_walls.length; i++)
        free(global_walls.buffer[i]);
    wall_array_destroy(&global_walls);
}

_ARRAY_DEFINE(Wall, wall)