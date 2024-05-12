#include "gui.h"
#include <stdlib.h>

GUI gui;

static float gui_vertices[] = {
     -1.0f, 0.95f, 0.0f, 0.0f, 0.6f,
     -1.0f, 1.0f, 0.0f, 0.0f, 0.6f,
    -0.85f, 0.95f, 0.0f, 0.0f, 0.6f,
     -1.0f, 1.0f, 0.0f, 0.0f, 0.6f,
     -0.85f, 1.0f, 0.0f, 0.0f, 0.6f,
     -0.85f,  0.95f, 0.0f, 0.0f, 0.6f
};

void gui_init(void)
{
    gui.buffer = malloc(10000 * sizeof(f32));
    gui.length = 0;
}

void gui_push_data(void)
{
    gui.length = 0;
    for (i32 i = 0; i < sizeof(gui_vertices) / sizeof(f32); i++)
        gui.buffer[gui.length++] = gui_vertices[i];
}

void gui_destroy(void)
{
    free(gui.buffer);
}