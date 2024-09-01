#ifndef DATA_H
#define DATA_H

#include "game/game.h"
#include "camera/camera.h"
#include "renderer/renderer.h"
#include "gui/gui.h"
#include "util/framedata.h"
#include "util/indices.h"

typedef struct {
    u32 vbo_length, ebo_length;
    f32 *vbo_buffer;
    u32 *ebo_buffer;
    FrameData ***frame_data;
} Data;

extern Data data;

void data_init(void);
void data_update(void);
void data_destroy(void);

#endif