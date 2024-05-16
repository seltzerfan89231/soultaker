#include "wall.h"
#include <stdlib.h>

Wall* wall_create(walltype type)
{
    Wall* wall = malloc(sizeof(Wall));
    wall->type = type;
    return wall;
}

void wall_push_data(Wall* wall, f32* buffer, u32 offset)
{
    offset *= 3;
    buffer[offset++] = wall->position.x;
    buffer[offset++] = wall->position.y;
    buffer[offset++] = wall->position.z;
}

void wall_remove_data(Wall* wall, f32* buffer, u32 offset)
{
    offset *= 3;
    buffer[offset++] = 0;
    buffer[offset++] = 0;
    buffer[offset++] = 0;
}

void wall_destroy(Wall* wall)
{
    free(wall);
}