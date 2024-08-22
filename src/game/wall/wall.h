#ifndef WALL_H
#define WALL_H

#include "../../util/array.h"
#include "../../util/type.h"
#include "../../util/vec.h"
#include "../../util/indices.h"

typedef struct {
    struct {
        i32 x, z;
    } position;
    u32 top_tex, side_tex, id;
    f32 height;
} Wall;

Wall* wall_create(u32 id, f32 x, f32 z, f32 height);
void wall_destroy(Wall* wall, u32 idx);
void destroy_all_walls(void);

_ARRAY_DECLARE(Wall, wall)
extern WallArray global_walls;

#define MAX_WALL_ID 1
#define DEFAULT_WALL 0

#endif