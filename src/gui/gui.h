#ifndef GUI_H
#define GUI_H

#include "../util/type.h"

typedef struct GUI {
    f32 *buffer;
    u32 length;
} GUI;

extern GUI gui;

void gui_init(void);
void gui_push_data(void);
void gui_destroy(void);

#endif