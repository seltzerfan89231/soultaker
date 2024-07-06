#include "wall.h"
#include <stdlib.h>

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
    return wall;
}

void wall_destroy(Wall* wall)
{
    free(wall);
}

_ARRAY_DEFINE(Wall, wall)