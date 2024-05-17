#include "wall.h"
#include <stdlib.h>

Wall* wall_create(walltype type)
{
    Wall* wall = malloc(sizeof(Wall));
    wall->type = type;
    return wall;
}

void wall_destroy(Wall* wall)
{
    free(wall);
}