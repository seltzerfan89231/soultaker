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
    gui.root->interactable = 0;
    //Component *test = component_create(0.0, 0.0, 0.3, 0.3, 0.7f, 0.2f, 0.4f, 0.5f);
    Component *btn = component_create(0.1, 0.8, 0.2, 0.9, 0.7f, 0.2f, 0.4f, 0.5f);
    //Component *test1 = component_create(0.0, 0.0, 0.9, 0.9, 0.7f, 0.2f, 0.4f, 0.5f);
    //Component *test2 = component_create(0.0, 0.0, 0.9, 0.9, 0.7f, 0.2f, 0.4f, 0.5f);
    //component_attach(gui.root, test);
    //component_attach(test, test1);
    //component_attach(test1, test2);
    component_attach(gui.root, btn);
}

void gui_push_data_helper(Component *comp, f32 x1, f32 y1, f32 x2, f32 y2)
{
    f32 new_x1, new_y1, new_x2, new_y2, win_x1, win_y1, win_x2, win_y2;
    new_x1 = comp->x1 * (x2 - x1) + x1, new_y1 = comp->y1 * (y2 - y1) + y1;
    new_x2 = comp->x2 * (x2 - x1) + x1, new_y2 = comp->y2 * (y2 - y1) + y1;
    win_x1 = 2 * (comp->x1 * (x2 - x1) - 0.5f) + x1, win_y1 = 2 * (comp->y1 * (y2 - y1) - 0.5f) + y1;
    win_x2 = 2 * (comp->x2 * (x2 - x1) - 0.5f) + x1, win_y2 = 2 * (comp->y2 * (y2 - y1) - 0.5f) + y1;
    Z = win_x1, Z = win_y1, Z = comp->r, Z = comp->g, Z = comp->b, Z = comp->a;
    Z = win_x2, Z = win_y1, Z = comp->r, Z = comp->g, Z = comp->b, Z = comp->a;
    Z = win_x1, Z = win_y2, Z = comp->r, Z = comp->g, Z = comp->b, Z = comp->a;
    Z = win_x1, Z = win_y2, Z = comp->r, Z = comp->g, Z = comp->b, Z = comp->a;
    Z = win_x2, Z = win_y1, Z = comp->r, Z = comp->g, Z = comp->b, Z = comp->a;
    Z = win_x2, Z = win_y2, Z = comp->r, Z = comp->g, Z = comp->b, Z = comp->a;
    for (i32 i = 0; i < comp->num_children; i++)
        gui_push_data_helper(comp->children[i], new_x1, new_y1, new_x2, new_y2);
}

void gui_push_data(void)
{
    gui.length = 0;
    gui_push_data_helper(gui.root, gui.root->x1, gui.root->y1, gui.root->x2, gui.root->y2);
}

bool gui_interact_helper(vec2f mouse_pos, Component *comp, f32 x1, f32 y1, f32 x2, f32 y2)
{
    f32 new_x1, new_y1, new_x2, new_y2, win_x1, win_y1, win_x2, win_y2;
    new_x1 = comp->x1 * (x2 - x1) + x1, new_y1 = comp->y1 * (y2 - y1) + y1;
    new_x2 = comp->x2 * (x2 - x1) + x1, new_y2 = comp->y2 * (y2 - y1) + y1;
    for (i32 i = 0; i < comp->num_children; i++)
        if (gui_interact_helper(mouse_pos, comp->children[i], new_x1, new_y1, new_x2, new_y2))
            return 1;
    if (!comp->interactable)
        return 0;
    if (mouse_pos.x >= new_x1 && mouse_pos.x <= new_x2 && 1 - mouse_pos.y >= new_y1 && 1 - mouse_pos.y <= new_y2) {
        puts("Hovered");
        return 1;
    }
    return 0;
}

bool gui_interact(vec2f mouse_pos)
{
    return gui_interact_helper(mouse_pos, gui.root, gui.root->x1, gui.root->y1, gui.root->x2, gui.root->y2);
}

void gui_destroy(void)
{
    component_destroy(gui.root);
    free(gui.buffer);
}