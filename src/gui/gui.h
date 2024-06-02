#ifndef GUI_H
#define GUI_H

#include "../util/type.h"
#include "component/component.h"

typedef struct {
    Component *root;
    u32 length, max_length;
    f32 *buffer;
} GUI;

extern GUI gui;

void gui_init(void);
void gui_push_data(void);
void gui_destroy(void);

#endif