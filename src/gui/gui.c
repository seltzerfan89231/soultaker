#include "gui.h"
#include <stdlib.h>
#include <stdio.h>

#define Z gui.buffer[gui.length++]

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
    gui.root = component_create(0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f);
    Component *test = component_create(0.0, 0.0, 0.3, 0.3, 0.7f, 0.2f, 0.4f, 0.5f);
    component_attach(gui.root, test);
}

void gui_push_data_helper(Component *comp, f32 x1, f32 y1, f32 x2, f32 y2)
{
    Z = 2 * (comp->x1 * (x2 - x1) - 0.5f) + x1, Z = 2 * (comp->y1 * (y2 - y1) - 0.5f) + y1, Z = comp->r, Z = comp->g, Z = comp->b, Z = comp->a;
    Z = 2 * (comp->x2 * (x2 - x1) - 0.5f) + x1, Z = 2 * (comp->y1 * (y2 - y1) - 0.5f) + y1, Z = comp->r, Z = comp->g, Z = comp->b, Z = comp->a;
    Z = 2 * (comp->x1 * (x2 - x1) - 0.5f) + x1, Z = 2 * (comp->y2 * (y2 - y1) - 0.5f) + y1, Z = comp->r, Z = comp->g, Z = comp->b, Z = comp->a;
    Z = 2 * (comp->x2 * (x2 - x1) - 0.5f) + x1, Z = 2 * (comp->y2 * (y2 - y1) - 0.5f) + y1, Z = comp->r, Z = comp->g, Z = comp->b, Z = comp->a;
    for (i32 i = 0; i < comp->num_children; i++)
        gui_push_data_helper(comp->children[i], comp->x1, comp->y1, comp->x2, comp->y2);
}

void gui_push_data(void)
{
    gui.length = 0;
    gui_push_data_helper(gui.root, 0.0f, 0.0f, 1.0f, 1.0f);
}

void gui_destroy(void)
{
    component_destroy(gui.root);
    free(gui.buffer);
}