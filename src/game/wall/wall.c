#include "wall.h"
#include "../tilemap/tilemap.h"
#include <stdlib.h>
#include <assert.h>

WallArray global_walls;

#define _CREATE(_id, _lid) \
    case _id : _lid##_create(wall); break;

Wall* wall_create(u32 id, f32 x, f32 z, f32 w, f32 h, f32 l)
{
    Wall* wall = malloc(sizeof(Wall));
    wall->id = id;
    wall->position.x = x;
    wall->position.z = z;
    wall->dimensions.w = w;
    wall->dimensions.h = h;
    wall->dimensions.l = l;
    wall->top_tex = WALL_TOP_TEX;
    wall->side1_tex = WALL_SIDE_TEX;
    wall->side2_tex = WALL_SIDE_TEX;
    switch(wall->id) {
        _CREATE(SHAITAN_WALL, shaitan_wall)
        _CREATE(SHAITAN_BARS, shaitan_bars)
    }
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