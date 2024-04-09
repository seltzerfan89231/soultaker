#include "gui.h"

static float gui_vertices[] = {
     -1.0f, 0.95f, 0.0f, 0.0f, 0.6f,
     -1.0f, 1.0f, 0.0f, 0.0f, 0.6f,
    -0.85f, 0.95f, 0.0f, 0.0f, 0.6f,
     -1.0f, 1.0f, 0.0f, 0.0f, 0.6f,
     -0.85f, 1.0f, 0.0f, 0.0f, 0.6f,
     -0.85f,  0.95f, 0.0f, 0.0f, 0.6f
};

void gui_push_data(f32* buffer, u32* length)
{
    for (i32 i = 0; i < sizeof(gui_vertices) / sizeof(f32); i++)
        buffer[(*length)++] = gui_vertices[i];
}