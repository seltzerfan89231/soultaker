#ifndef WALL_H
#define WALL_H

#include "../../util/type.h"
#include "../../util/vec.h"

typedef enum { WALL2 } walltype;

typedef struct {
    vec2i position;
    f32 height;
    walltype type;
} Wall;

Wall* wall_create(walltype type);
void wall_destroy(Wall* wall);

#endif