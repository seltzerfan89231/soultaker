#ifndef WALL_H
#define WALL_H

#include "../../util/array.h"
#include "../../util/type.h"
#include "../../util/vec.h"
#include "../../util/indices.h"

typedef enum { WALL2 } walltype;

typedef struct {
    struct {
        i32 x, z;
    } position;
    u32 top_tex, side_tex;
    f32 height;
    walltype type;
} Wall;

Wall* wall_create(walltype type, f32 x, f32 z, f32 height);
void wall_destroy(Wall* wall, u32 idx);

_ARRAY_DECLARE(Wall, wall)
extern WallArray walls;

#endif