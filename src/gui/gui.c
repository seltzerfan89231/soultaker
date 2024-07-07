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
    char_map_init();
    gui.max_length = 1000;
    gui.buffer = malloc(gui.max_length * sizeof(f32));
    gui.length = 0;
    gui.root = component_create(0.0f, 0.0f, 1.0f, 1.0f, 0.0f, NO_TEX);
    gui.root->interactable = 0;
    Component *btn = component_create(0.05f, 0.05f, 0.1f, 0.1f, 1.0f, BUTTON_TEX);
    btn->action = 1;
    component_attach(gui.root, btn);
    Component *healthbar = component_create(0.05, 0.92, 0.2, 0.02, 0.0, NO_TEX);
    component_attach(gui.root, healthbar);
    Component *green_part = component_create(0.0, 0.0, 0.75, 1.0, 1.0, EMPTY_TEX);
    green_part->g = 1.0, green_part->r = 0.0, green_part->b = 0.0;
    component_attach(healthbar, green_part);
    Component *red_part = component_create(0.75, 0.0, 0.25, 1.0, 1.0, EMPTY_TEX);
    red_part->r = 1.0, red_part->g = red_part->b = 0.0;
    component_attach(healthbar, red_part);
}

#define Z gui.buffer[gui.length++]

void gui_push_data_helper(Component *comp, f32 x, f32 y, f32 w, f32 h)
{
    f32 new_x1, new_y1, new_x2, new_y2, win_x1, win_x2, win_y1, win_y2;
    new_x1 = comp->x * w + x, new_x2 = (comp->x + comp->w) * w + x;
    new_y1 = comp->y * h + y, new_y2 = (comp->y + comp->h) * h + y;
    win_x1 = 2 * (new_x1 / (comp == gui.root ? 1 : window.aspect_ratio) - 0.5f), win_y1 = 2 * (new_y1 - 0.5f);
    win_x2 = 2 * (new_x2 / (comp == gui.root ? 1 : window.aspect_ratio) - 0.5f), win_y2 = 2 * (new_y2 - 0.5f);
    if (gui.length + 36 >= gui.max_length) {
        gui.max_length += 1000;
        gui.buffer = realloc(gui.buffer, gui.max_length * sizeof(f32));
    }
    Z = win_x1, Z = win_y1, Z = 0.0f, Z = 1.0f, Z = comp->id, Z = comp->r, Z = comp->g, Z = comp->b, Z = comp->a;
    Z = win_x2, Z = win_y1, Z = 1.0f, Z = 1.0f, Z = comp->id, Z = comp->r, Z = comp->g, Z = comp->b, Z = comp->a;
    Z = win_x1, Z = win_y2, Z = 0.0f, Z = 0.0f, Z = comp->id, Z = comp->r, Z = comp->g, Z = comp->b, Z = comp->a;
    Z = win_x1, Z = win_y2, Z = 0.0f, Z = 0.0f, Z = comp->id, Z = comp->r, Z = comp->g, Z = comp->b, Z = comp->a;
    Z = win_x2, Z = win_y1, Z = 1.0f, Z = 1.0f, Z = comp->id, Z = comp->r, Z = comp->g, Z = comp->b, Z = comp->a;
    Z = win_x2, Z = win_y2, Z = 1.0f, Z = 0.0f, Z = comp->id, Z = comp->r, Z = comp->g, Z = comp->b, Z = comp->a;
    for (i32 i = 0; i < comp->num_children; i++)
        gui_push_data_helper(comp->children[i], new_x1, new_y1, new_x2 - new_x1, new_y2 - new_y1);
}

void gui_push_data(void)
{
    gui.length = 0;
    gui_push_data_helper(gui.root, gui.root->x, gui.root->y, gui.root->w, gui.root->h);
}

u32 gui_interact_helper(vec2f cursor_pos, Component *comp, f32 x, f32 y, f32 w, f32 h)
{
    f32 new_x1, new_y1, new_x2, new_y2, win_x1, win_x2, win_y1, win_y2;
    new_x1 = comp->x * w + x, new_x2 = (comp->x + comp->w) * w + x;
    new_y1 = comp->y * h + y, new_y2 = (comp->y + comp->h) * h + y;
    for (i32 i = 0; i < comp->num_children; i++) {
        u32 action = gui_interact_helper(cursor_pos, comp->children[i], new_x1, new_y1, new_x2 - new_x1, new_y2 - new_y1);
        if (action)
            return action;
    }
    if (!comp->interactable)
        return FALSE;
    if (cursor_pos.x >= new_x1 && cursor_pos.x <= new_x2 && 1 - cursor_pos.y >= new_y1 && 1 - cursor_pos.y <= new_y2)
        return comp->action;
    return FALSE;
}

u32 gui_interact(void)
{
    vec2f cursor_pos = window.cursor.position;
    cursor_pos.x *= window.aspect_ratio;
    return gui_interact_helper(cursor_pos, gui.root, gui.root->x, gui.root->y, gui.root->w, gui.root->h);
}

bool gui_hover_helper(vec2f cursor_pos, Component *comp, f32 x, f32 y, f32 w, f32 h)
{
    f32 new_x1, new_y1, new_x2, new_y2, win_x1, win_x2, win_y1, win_y2;
    new_x1 = comp->x * w + x, new_x2 = (comp->x + comp->w) * w + x;
    new_y1 = comp->y * h + y, new_y2 = (comp->y + comp->h) * h + y;
    for (i32 i = 0; i < comp->num_children; i++) {
        bool hovered = gui_hover_helper(cursor_pos, comp->children[i], new_x1, new_y1, new_x2 - new_x1, new_y2 - new_y1);
        if (hovered)
            return hovered;
    }
    if (!comp->interactable)
        return FALSE;
    if (cursor_pos.x >= new_x1 && cursor_pos.x <= new_x2 && 1 - cursor_pos.y >= new_y1 && 1 - cursor_pos.y <= new_y2)
        return TRUE;
    return FALSE;
}

bool gui_hover(void)
{
    vec2f cursor_pos = window.cursor.position;
    cursor_pos.x *= window.aspect_ratio;
    return gui_hover_helper(cursor_pos, gui.root, gui.root->x, gui.root->y, gui.root->w, gui.root->h);
}

void gui_destroy(void)
{
    component_destroy(gui.root);
    free(gui.buffer);
}