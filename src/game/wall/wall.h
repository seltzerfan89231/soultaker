#ifndef WALL_H
#define WALL_H

#include "../../util/type.h"
#include "../../util/vec.h"

typedef enum { WALL2 } walltype;

typedef struct {
    struct {
        i32 x, z;
    } position;
    f32 height;
    walltype type;
} Wall;

Wall* wall_create(walltype type, f32 x, f32 z, f32 height);
void wall_destroy(Wall* wall);

#endif