#ifndef GUI_H
#define GUI_H

#include "../../util/type.h"

typedef struct gui {
    int x;
} gui;

void gui_push_data(f32* buffer, u32* length);

#endif