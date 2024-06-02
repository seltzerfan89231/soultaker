#include "gui.h"
#include <stdlib.h>
#include <stdio.h>

GUI gui;

static float gui_vertices[] = {
     -1.0f, 0.95f, 0.0f, 0.0f, 0.6f,
     -0.85f, 0.95f, 0.0f, 0.0f, 0.6f,
     -1.0f, 1.0f, 0.0f, 0.0f, 0.6f,
     -0.85f, 1.0f, 0.0f, 0.0f, 0.6f,
};

void confirm_click(void)
{
    puts("Clicked!");
}

void gui_init(void)
{
    gui.max_length = 1000;
    gui.buffer = malloc(gui.max_length * sizeof(f32));
    gui.length = 0;
    gui.root = component_create(0.0f, 0.0f, 1.0f, 1.0f);
    Component *test = component_create(0.0, 0.0, 0.5, 0.5);
    component_attach(gui.root, test);
    component_detach(gui.root, test);
    component_destroy(test);
}

void gui_push_data(void)
{
    gui.length = 0;
    for (i32 i = 0; i < sizeof(gui_vertices) / sizeof(f32); i++)
        gui.buffer[gui.length++] = gui_vertices[i];
}

void gui_destroy(void)
{
    component_destroy(gui.root);
    free(gui.buffer);
}