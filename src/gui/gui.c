#include "gui.h"
#include <stdlib.h>
#include <stdio.h>

GUI gui;
extern Window window;

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
    component_init();
    gui.max_length = 1000;
    gui.buffer = malloc(gui.max_length * sizeof(f32));
    gui.length = 0;
    gui.root = component_create(0.0f, 0.0f, 1.0f, 1.0f, 0.0f, NO_TEX);
    gui.root->interactable = 0;
    Component *btn = component_create(0.1, 0.5, 0.4, 0.4, 0.2f, EMPTY_TEX);
    //Component *txt = component_create(0.1, 0.1, 0.15, 0.17, 0, 1.0f);
    component_attach(gui.root, btn);
    component_add_text(gui.root, "ABC BAB", 15, 1.0f, 1.0f);
    component_add_text(btn, "ABABABABABABABAB", 15, 0.4f, 0.4f);
    //component_attach(btn, txt);
}

#define Z gui.buffer[gui.length++]

void gui_push_data_helper(Component *comp, f32 x, f32 y, f32 w, f32 h)
{
    f32 new_x1, new_y1, new_x2, new_y2, win_x1, win_x2, win_y1, win_y2;
    new_x1 = comp->x * w + x, new_x2 = (comp->x + comp->w) * w + x;
    new_y1 = comp->y * h + y, new_y2 = (comp->y + comp->h) * h + y;
    win_x1 = 2 * (new_x1 / (comp == gui.root ? 1 : window.aspect_ratio) - 0.5f), win_y1 = 2 * (new_y1 - 0.5f);
    win_x2 = 2 * (new_x2 / (comp == gui.root ? 1 : window.aspect_ratio) - 0.5f), win_y2 = 2 * (new_y2 - 0.5f);
    Z = win_x1, Z = win_y1, Z = 0.0f, Z = 1.0f, Z = comp->id, Z = comp->a;
    Z = win_x2, Z = win_y1, Z = 1.0f, Z = 1.0f, Z = comp->id, Z = comp->a;
    Z = win_x1, Z = win_y2, Z = 0.0f, Z = 0.0f, Z = comp->id, Z = comp->a;
    Z = win_x1, Z = win_y2, Z = 0.0f, Z = 0.0f, Z = comp->id, Z = comp->a;
    Z = win_x2, Z = win_y1, Z = 1.0f, Z = 1.0f, Z = comp->id, Z = comp->a;
    Z = win_x2, Z = win_y2, Z = 1.0f, Z = 0.0f, Z = comp->id, Z = comp->a;
    for (i32 i = 0; i < comp->num_children; i++)
        gui_push_data_helper(comp->children[i], new_x1, new_y1, new_x2 - new_x1, new_y2 - new_y1);
}

void gui_push_data(void)
{
    gui.length = 0;
    gui_push_data_helper(gui.root, gui.root->x, gui.root->y, gui.root->w, gui.root->h);
}

bool gui_interact_helper(vec2f mouse_pos, Component *comp, f32 x, f32 y, f32 w, f32 h)
{
    f32 new_x1, new_y1, new_x2, new_y2, win_x1, win_x2, win_y1, win_y2;
    new_x1 = comp->x * w + x, new_x2 = (comp->x + comp->w) * w + x;
    new_y1 = comp->y * h + y, new_y2 = (comp->y + comp->h) * h + y;
    for (i32 i = 0; i < comp->num_children; i++)
        if (gui_interact_helper(mouse_pos, comp->children[i], new_x1, new_y1, new_x2 - new_x1, new_y2 - new_y1))
            return 1;
    if (!comp->interactable)
        return 0;
    if (mouse_pos.x >= new_x1 && mouse_pos.x <= new_x2 && 1 - mouse_pos.y >= new_y1 && 1 - mouse_pos.y <= new_y2) {
        puts("Hovered");
        return 1;
    }
    return 0;
}

bool gui_interact(void)
{
    vec2f mouse_pos = window.mouse.position;
    mouse_pos.x *= window.aspect_ratio;
    return gui_interact_helper(mouse_pos, gui.root, gui.root->x, gui.root->y, gui.root->w, gui.root->h);
}

void gui_destroy(void)
{
    component_destroy(gui.root);
    free(gui.buffer);
}