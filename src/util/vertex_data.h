#ifndef VERTEX_DATA_H
#define VERTEX_DATA_H

#include "type.h"

#define MAX_BUFFER_LENGTH 1000000
#define QUAD_VERTEX_COUNT 6
#define TILE_VERTEX_LENGTH 5
#define GUI_VERTEX_LENGTH 5

static f32 vertices[] = {
    0, 0, 0,
    1, 0, 0,
    1, 1, 0,
    0, 1, 0,
    0, 0, 1,
    1, 0, 1,
    1, 1, 1,
    0, 1, 1
};

static u32 sides[] = {
    2, 1, 0, 3, //-z
    7, 4, 5, 6, //+z
    6, 5, 1, 2, //+x
    3, 0, 4, 7, //-x
    2, 3, 7, 6, //+y
    0, 4, 5, 1  //-y
};

static u32 tex[] = {
    1, 1,
    1, 0,
    0, 0,
    0, 1
};

static u32 vertex_order[] = {
    0, 1, 2, 0, 2, 3
};

#endif