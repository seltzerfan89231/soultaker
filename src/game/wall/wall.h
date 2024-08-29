#ifndef WALL_H
#define WALL_H

#include "../../util/array.h"
#include "../../util/type.h"
#include "../../util/vec.h"
#include "../../util/indices.h"

typedef struct {
    struct {
        f32 x, z;
    } position;
    struct {
        f32 w, h, l;
    } dimensions;
    u32 top_tex, side1_tex, side2_tex, id;
} Wall;

Wall* wall_create(u32 id, f32 x, f32 z, f32 w, f32 h, f32 l);
void wall_destroy(Wall* wall, u32 idx);
void destroy_all_walls(void);

_ARRAY_DECLARE(Wall, wall)
extern WallArray global_walls;

#define MAX_WALL_ID 4
#define INVISIBLE_WALL 0
#define DEFAULT_WALL 1
#define SHAITAN_WALL 2
#define SHAITAN_BARS 3

#define _WALL_INIT(_type) \
    void _type##_create(Wall *wall);

_WALL_INIT(shaitan_wall)
_WALL_INIT(shaitan_bars)

#endif