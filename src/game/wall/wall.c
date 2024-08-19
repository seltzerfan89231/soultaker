#include "wall.h"
#include "../tilemap/tilemap.h"
#include <stdlib.h>
#include <assert.h>

WallArray walls;

Wall* wall_create(walltype type, f32 x, f32 z, f32 height)
{
    Wall* wall = malloc(sizeof(Wall));
    wall->type = type;
    wall->position.x = x;
    wall->position.z = z;
    wall->height = height;
    wall->top_tex = WALL_TOP_TEX;
    wall->side_tex = WALL_SIDE_TEX;
    wall_array_push(&walls, wall);
    tilemap_insert_wall(wall);
    return wall;
}

void wall_destroy(Wall* wall, u32 idx)
{
    assert(wall == walls.buffer[idx]);
    wall_array_cut(&walls, idx);
    free(wall);
}

void destroy_all_walls(void)
{
    for (i32 i = 0; i < walls.length; i++)
        free(walls.buffer[i]);
    wall_array_destroy(&walls);
}


_ARRAY_DEFINE(Wall, wall)