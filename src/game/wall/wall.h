#ifndef WALL_H
#define WALL_H

#include "../../util/type.h"
#include "../../util/vec.h"

typedef enum { WALL2 } walltype;

typedef struct {
    vec3i position;
    walltype type;
} Wall;

Wall* wall_create(walltype type);
void wall_push_data(Wall* wall, f32* buffer, u32 offset);
void wall_remove_data(Wall* wall, f32* buffer, u32 offset);
void wall_destroy(Wall* wall);

#endif