#include "gui.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

GUI gui;
extern Window window;
extern Component *comp_root;

static float gui_vertices[] = {
     -1.0f, 0.95f, 0.0f, 0.0f, 0.6f,
     -0.85f, 0.95f, 0.0f, 0.0f, 0.6f,
     -1.0f, 1.0f, 0.0f, 0.0f, 0.6f,
     -0.85f, 1.0f, 0.0f, 0.0f, 0.6f,
};

void gui_init(void)
{
    char_map_init();
    gui.max_length = 1000;
    gui.buffer = malloc(gui.max_length * sizeof(f32));
    gui.length = 0;
    comp_root = component_create(0.0f, 0.0f, 1.0f, 1.0f, NO_TEX);
    comp_root->a = 0;
    gui.max_length_changed = TRUE;

    Component *title_card = component_create(0.3, 0.6, 0.4, 0.4 * 2.0/3, SOULTAKER_LOGO_TEX);
    title_card->hoverable = TRUE;
    title_card->interactable = TRUE;
    title_card->id = COMP_START_BUTTON;
    component_attach(comp_root, title_card);
}

#define Z gui.buffer[gui.length++]

void gui_update_data_add_text(Component *comp, f32 gx, f32 gy, f32 gw, f32 gh)
{
    if (comp->text == NULL)
        return;
    f32 pixel_size, w, h, px, py, bx, by, ox, oy, lx, ly, adv;
    f32 new_x1, new_y1, new_x2, new_y2, win_x1, win_x2, win_y1, win_y2;
    u32 length, i;
    char *text = comp->text;
    u32 font_size = 14;
    pixel_size = (f32)font_size / (DEFAULT_WINDOW_HEIGHT);
    px = pixel_size * 2 / gw;
    py = pixel_size * 0.5 / gh;
    length = strlen(text);
    ox = oy = 0;
    if (gui.length + 54 * length >= gui.max_length) {
        gui.max_length += 54 * length;
        gui.buffer = realloc(gui.buffer, gui.max_length * sizeof(f32));
        gui.max_length_changed = TRUE;
    }
    for (i = 0; i < length; i++) {
        Character c = char_map[text[i]];
        w = pixel_size / gw * c.size.x / c.size.y;
        h = pixel_size / gh;
        bx = pixel_size * c.bearing.x / gw;
        by = pixel_size * c.bearing.y / gh;
        adv = pixel_size * c.advance / gw;
        if (text[i] != ' ' && ox + adv > 1)
            ox = 0, oy += h + py;
        lx = ox + bx;
        ly = 1 - h - by - oy;
        //Component *letter = component_create(ox + bx, 1 - h - by - oy, w, h, c.tex);
        ox += adv;
        new_x1 = lx * gw + gx, new_x2 = (lx + w) * gw + gx;
        new_y1 = ly * gh + gy, new_y2 = (ly + h) * gh + gy;
        win_x1 = 2 * (new_x1 / window.aspect_ratio - 0.5f), win_y1 = 2 * (new_y1 - 0.5f);
        win_x2 = 2 * (new_x2 / window.aspect_ratio - 0.5f), win_y2 = 2 * (new_y2 - 0.5f);
        Z = win_x1, Z = win_y1, Z = 0.0f, Z = 1.0f, Z = c.tex, Z = comp->r, Z = comp->g, Z = comp->b, Z = comp->a;
        Z = win_x2, Z = win_y1, Z = 1.0f, Z = 1.0f, Z = c.tex, Z = comp->r, Z = comp->g, Z = comp->b, Z = comp->a;
        Z = win_x1, Z = win_y2, Z = 0.0f, Z = 0.0f, Z = c.tex, Z = comp->r, Z = comp->g, Z = comp->b, Z = comp->a;
        Z = win_x1, Z = win_y2, Z = 0.0f, Z = 0.0f, Z = c.tex, Z = comp->r, Z = comp->g, Z = comp->b, Z = comp->a;
        Z = win_x2, Z = win_y1, Z = 1.0f, Z = 1.0f, Z = c.tex, Z = comp->r, Z = comp->g, Z = comp->b, Z = comp->a;
        Z = win_x2, Z = win_y2, Z = 1.0f, Z = 0.0f, Z = c.tex, Z = comp->r, Z = comp->g, Z = comp->b, Z = comp->a;
    }
}

void gui_update_data_helper(Component *comp, f32 x, f32 y, f32 w, f32 h)
{
    f32 new_x1, new_y1, new_x2, new_y2, win_x1, win_x2, win_y1, win_y2;
    if (comp->relative) {
        new_x1 = comp->x * w + x, new_x2 = (comp->x + comp->w) * w + x;
        new_y1 = comp->y * h + y, new_y2 = (comp->y + comp->h) * h + y;
    } else {
        new_x1 = comp->x, new_x2 = comp->x + comp->w;
        new_y1 = comp->y, new_y2 = comp->y + comp->h;
    }
    win_x1 = 2 * (new_x1 / (comp == comp_root ? 1 : window.aspect_ratio) - 0.5f), win_y1 = 2 * (new_y1 - 0.5f);
    win_x2 = 2 * (new_x2 / (comp == comp_root ? 1 : window.aspect_ratio) - 0.5f), win_y2 = 2 * (new_y2 - 0.5f);
    if (gui.length + 54 >= gui.max_length) {
        gui.max_length += 1000;
        gui.buffer = realloc(gui.buffer, gui.max_length * sizeof(f32));
        gui.max_length_changed = TRUE;
    }
    Z = win_x1, Z = win_y1, Z = 0.0f, Z = 1.0f, Z = comp->tex, Z = comp->r, Z = comp->g, Z = comp->b, Z = comp->a;
    Z = win_x2, Z = win_y1, Z = 1.0f, Z = 1.0f, Z = comp->tex, Z = comp->r, Z = comp->g, Z = comp->b, Z = comp->a;
    Z = win_x1, Z = win_y2, Z = 0.0f, Z = 0.0f, Z = comp->tex, Z = comp->r, Z = comp->g, Z = comp->b, Z = comp->a;
    Z = win_x1, Z = win_y2, Z = 0.0f, Z = 0.0f, Z = comp->tex, Z = comp->r, Z = comp->g, Z = comp->b, Z = comp->a;
    Z = win_x2, Z = win_y1, Z = 1.0f, Z = 1.0f, Z = comp->tex, Z = comp->r, Z = comp->g, Z = comp->b, Z = comp->a;
    Z = win_x2, Z = win_y2, Z = 1.0f, Z = 0.0f, Z = comp->tex, Z = comp->r, Z = comp->g, Z = comp->b, Z = comp->a;
    gui_update_data_add_text(comp, new_x1, new_y1, new_x2 - new_x1, new_y2 - new_y1);
    for (i32 i = 0; i < comp->num_children; i++)
        gui_update_data_helper(comp->children[i], new_x1, new_y1, new_x2 - new_x1, new_y2 - new_y1);
}

void gui_update_data(void)
{
    gui.length = 0;
    gui_update_data_helper(comp_root, comp_root->x, comp_root->y, comp_root->w, comp_root->h);
}

static bool cursor_in_bounds(f32 x1, f32 x2, f32 y1, f32 y2)
{
    return window.cursor.position.x * window.aspect_ratio >= x1 
           && window.cursor.position.x * window.aspect_ratio <= x2 
           && 1 - window.cursor.position.y >= y1 
           && 1 - window.cursor.position.y <= y2;
}

void gui_update_helper(Component *comp, f32 x, f32 y, f32 w, f32 h)
{
    f32 new_x1, new_y1, new_x2, new_y2, win_x1, win_x2, win_y1, win_y2;
    new_x1 = comp->x * w + x, new_x2 = (comp->x + comp->w) * w + x;
    new_y1 = comp->y * h + y, new_y2 = (comp->y + comp->h) * h + y;
    if (comp->update_children)
        for (i32 i = 0; i < comp->num_children; i++)
            gui_update_helper(comp->children[i], new_x1, new_y1, new_x2 - new_x1, new_y2 - new_y1);
    component_update(comp);
    if (!comp->hoverable)
        return;
    component_hover_callback(comp, cursor_in_bounds(new_x1, new_x2, new_y1, new_y2));
}

bool gui_update(void)
{
    gui_update_helper(comp_root, comp_root->x, comp_root->y, comp_root->w, comp_root->h);
    gui_update_data();
    if (gui.max_length_changed) {
        renderer_malloc(GUI_VAO, gui.max_length);
        gui.max_length_changed = FALSE;
    }
    renderer_update(GUI_VAO, 0, gui.length, gui.buffer);
    return FALSE;
}

void gui_mouse_button_callback_helper(Component *comp, f32 x, f32 y, f32 w, f32 h, i32 button, i32 action)
{
    f32 new_x1, new_y1, new_x2, new_y2, win_x1, win_x2, win_y1, win_y2;
    new_x1 = comp->x * w + x, new_x2 = (comp->x + comp->w) * w + x;
    new_y1 = comp->y * h + y, new_y2 = (comp->y + comp->h) * h + y;
    if (comp->update_children)
        for (i32 i = 0; i < comp->num_children; i++)
            gui_mouse_button_callback_helper(comp->children[i], new_x1, new_y1, new_x2 - new_x1, new_y2 - new_y1, button, action);
    if (comp->interactable && cursor_in_bounds(new_x1, new_x2, new_y1, new_y2))
        component_mouse_button_callback(comp, button, action);
}

void gui_mouse_button_callback(i32 button, i32 action)
{
    gui_mouse_button_callback_helper(comp_root, comp_root->x, comp_root->y, comp_root->w, comp_root->h, button, action);
}

void gui_key_callback_helper(Component *comp, f32 x, f32 y, f32 w, f32 h, i32 key, i32 scancode, i32 action, i32 mods)
{
    f32 new_x1, new_y1, new_x2, new_y2, win_x1, win_x2, win_y1, win_y2;
    new_x1 = comp->x * w + x, new_x2 = (comp->x + comp->w) * w + x;
    new_y1 = comp->y * h + y, new_y2 = (comp->y + comp->h) * h + y;
    if (comp->update_children)
        for (i32 i = 0; i < comp->num_children; i++)
            gui_key_callback_helper(comp->children[i], new_x1, new_y1, new_x2 - new_x1, new_y2 - new_y1, key, scancode, action, mods);
    if (comp->interactable && cursor_in_bounds(new_x1, new_x2, new_y1, new_y2))
        component_key_callback(comp, key, scancode, action, mods);
}

void gui_key_callback(i32 key, i32 scancode, i32 action, i32 mods)
{
    gui_key_callback_helper(comp_root, comp_root->x, comp_root->y, comp_root->w, comp_root->h, key, scancode, action, mods);
}

void gui_destroy(void)
{
    component_destroy(comp_root);
    free(gui.buffer);
}