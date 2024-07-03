#ifndef FRAME_DATA_H
#define FRAME_DATA_H

#include "type.h"

#define _FD(_x, _y, _w, _h, _frame) \
    (FrameData) { .x = _x , .y = _y , .w = _w , .h = _h , .frame = _frame };

#define _FDdef(_frame) \
    (FrameData) { .x = 0.0f , .y = 0.0f , .w = 1.0f , .h = 1.0f , .frame = _frame };

typedef struct {
    f32 x, y, w, h;
    u32 frame;
} FrameData;

#endif