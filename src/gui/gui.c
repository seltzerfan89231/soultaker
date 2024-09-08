#include "gui.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

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
    gui.vbo_max_length = gui.ebo_max_length = 0;
    gui.vbo_length = gui.ebo_length = 0;
    gui.vbo_buffer = malloc(gui.vbo_max_length * sizeof(f32));
    gui.ebo_buffer = malloc(gui.ebo_max_length * sizeof(u32));
    
    comp_root = component_create(0.0f, 0.0f, 1.0f, 1.0f, COMP_DEFAULT, NO_TEX);
    comp_root->a = 0;
    gui.max_length_changed = TRUE;

    component_attach(comp_root, component_create(window.aspect_ratio / 2 - 0.2, 0.7, 0.4, 0.4 * 2.0/3, COMP_SINGLEPLAYER, COLOR_TEX));
    component_attach(comp_root, component_create(window.aspect_ratio / 2 - 0.2, 0.3, 0.4, 0.4 * 2.0/3, COMP_MULTIPLAYER, COLOR_TEX));
    Component *comp = component_create(0.15, 0.1, 0.4, 0.4, COMP_DEFAULT, COLOR_TEX);
    comp->a = 0.3;
    comp->center_text = TRUE;
    component_set_text(comp, 14, "The quick brown fox jumped over the lazy dog. The quick brown fox jumped over the lazy dog.");
    component_attach(comp_root, comp);
}

bool gui_input_paused(void)
{
    return component_input_paused();
}

#define Z gui.vbo_buffer[gui.vbo_length++]
#define V gui.ebo_buffer[gui.ebo_length++]

static void resize_gui_buffers(u32 added_vbo_length)
{
    if (gui.vbo_length + 9 * 4 * added_vbo_length >= gui.vbo_max_length) {
        gui.vbo_max_length += 9 * 4 * added_vbo_length;
        gui.ebo_max_length += 6 * added_vbo_length;
        gui.vbo_buffer = realloc(gui.vbo_buffer, gui.vbo_max_length * sizeof(f32));
        gui.ebo_buffer = realloc(gui.ebo_buffer, gui.ebo_max_length * sizeof(u32));
        gui.max_length_changed = TRUE;
    }
}

static i32 get_num_lines(Component *comp, f32 w, f32 h)
{
    f32 pixel_size, pixel_size_x, pixel_size_y, glyph_size_y, px, py, bx, by, ox, oy, lx, ly, lw, lh, adv;
    i32 length, left, right, right_copy, nl;
    char *text = comp->text;
    length = strlen(text);
    pixel_size = (f32)comp->font_size / (DEFAULT_WINDOW_HEIGHT) / GLYPH_HEIGHT;
    pixel_size_x = pixel_size / w;
    pixel_size_y = pixel_size / h;
    glyph_size_y = pixel_size_y * GLYPH_HEIGHT;
    px = pixel_size_x;
    py = pixel_size_y * (2 - MIN_BEARING_Y);
    nl = 0;
    while (right < length) {
        f32 test_ox = -px;
        while (left != 0 && right < length && text[right] == ' ' || text[right] == '\t')
            right++;
        left = right;
        while (right < length && text[right] != '\n' && test_ox <= 1) {
            Character c = char_map[text[right]];
            test_ox += pixel_size_x * c.advance + px;
            right++;
        }
        if (right < length && text[right] == '\n')
            right++;
        right_copy = (test_ox > 1) ? right - 1 : right;
        if (test_ox > 1) {
            do {
                right--;
                Character c = char_map[text[right]];
                test_ox -= pixel_size_x * c.advance + px;
            } while (right > left && text[right-1] != ' ' && text[right-1] != '\t');
            while (right > left && (text[right-1] == ' ' || text[right-1] == '\t')) { 
                right--;
                Character c = char_map[text[right]];
                test_ox -= pixel_size_x * c.advance + px;
            } 
        }
        if (left == right)
            right = right_copy;
        ox = 0;
        while (left < right && left < length) {
            if (text[left] == '\n') {
                left++;
                continue;
            }
            Character c = char_map[text[left]];
            lw = pixel_size_x * c.size.x;
            lh = pixel_size_y * c.size.y;
            bx = pixel_size_x * c.bearing.x;
            by = pixel_size_y * c.bearing.y;
            adv = pixel_size_x * c.advance;
            lx = ox + bx;
            ly = (comp->down_text) ? oy + by : 1 - glyph_size_y + by - oy;
            ox += adv + px;
            left++;
        }
        oy += glyph_size_y + py;
        nl++;
    }
    return nl;
}

static void update_text_data(Component *comp, i32 nl, f32 x, f32 y, f32 w, f32 h)
{
    f32 pixel_size, pixel_size_x, pixel_size_y, glyph_size_y, px, py, bx, by, ox, oy, lx, ly, lw, lh, adv;
    f32 new_x1, new_y1, new_x2, new_y2, win_x1, win_x2, win_y1, win_y2;
    i32 length, left, right, right_copy;
    char *text = comp->text;
    length = strlen(text);
    pixel_size = (f32)comp->font_size / (DEFAULT_WINDOW_HEIGHT) / GLYPH_HEIGHT;
    pixel_size_x = pixel_size / w;
    pixel_size_y = pixel_size / h;
    glyph_size_y = pixel_size_y * GLYPH_HEIGHT;
    px = pixel_size_x;
    py = pixel_size_y * (2 - MIN_BEARING_Y);
    oy = (comp->center_text) ? 0.5 - (nl * glyph_size_y + (nl - 1) * py) / 2 : 0;
    left = right = 0;
    while (right < length) {
        f32 test_ox = -px;
        while (left != 0 && right < length && text[right] == ' ' || text[right] == '\t')
            right++;
        left = right;
        while (right < length && text[right] != '\n' && test_ox <= 1) {
            Character c = char_map[text[right]];
            test_ox += pixel_size_x * c.advance + px;
            right++;
        }
        if (right < length && text[right] == '\n')
            right++;
        right_copy = (test_ox > 1) ? right - 1 : right;
        if (test_ox > 1) {
            do {
                right--;
                Character c = char_map[text[right]];
                test_ox -= pixel_size_x * c.advance + px;
            } while (right > left && text[right-1] != ' ' && text[right-1] != '\t');
            while (right > left && (text[right-1] == ' ' || text[right-1] == '\t')) { 
                right--;
                Character c = char_map[text[right]];
                test_ox -= pixel_size_x * c.advance + px;
            } 
        }
        if (left == right)
            right = right_copy;
        ox = (comp->center_text) ? (1.0 - test_ox) / 2.0 : 0;
        while (left < right && left < length) {
            if (text[left] == '\n') {
                left++;
                continue;
            }
            Character c = char_map[text[left]];
            lw = pixel_size_x * c.size.x;
            lh = pixel_size_y * c.size.y;
            bx = pixel_size_x * c.bearing.x;
            by = pixel_size_y * c.bearing.y;
            adv = pixel_size_x * c.advance;
            lx = ox + bx;
            ly = (comp->down_text) ? oy + by : 1 - glyph_size_y + by - oy;
            ox += adv + px;
            new_x1 = lx * w + x, new_x2 = (lx + lw) * w + x;
            new_y1 = ly * h + y, new_y2 = (ly + lh) * h + y;
            win_x1 = 2 * (new_x1 / window.aspect_ratio - 0.5f), win_y1 = 2 * (new_y1 - 0.5f);
            win_x2 = 2 * (new_x2 / window.aspect_ratio - 0.5f), win_y2 = 2 * (new_y2 - 0.5f);
            u32 idx = gui.vbo_length / 9;
            if (text[left] != ' ' && text[left] != '\t') {
                Z = win_x1, Z = win_y1, Z = 0.0f, Z = 1.0f, Z = c.tex, Z = 1.0f, Z = 1.0f, Z = 1.0f, Z = 1.0f;
                Z = win_x2, Z = win_y1, Z = 1.0f, Z = 1.0f, Z = c.tex, Z = 1.0f, Z = 1.0f, Z = 1.0f, Z = 1.0f;
                Z = win_x1, Z = win_y2, Z = 0.0f, Z = 0.0f, Z = c.tex, Z = 1.0f, Z = 1.0f, Z = 1.0f, Z = 1.0f;
                Z = win_x2, Z = win_y2, Z = 1.0f, Z = 0.0f, Z = c.tex, Z = 1.0f, Z = 1.0f, Z = 1.0f, Z = 1.0f;
                V = idx, V = idx + 1, V = idx + 2, V = idx + 2, V = idx + 1, V = idx + 3;
            }
            left++;
        }
        oy += glyph_size_y + py;
    }
}

void gui_update_data_add_text(Component *comp, f32 x, f32 y, f32 w, f32 h)
{
    if (comp->text == NULL)
        return;
    resize_gui_buffers(strlen(comp->text));
    if (comp->center_text)
        update_text_data(comp, get_num_lines(comp, w, h), x, y, w, h);
    else
        update_text_data(comp, 0, x, y, w, h);
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
    resize_gui_buffers(1);
    u32 idx = gui.vbo_length / 9;
    Z = win_x1, Z = win_y1, Z = 0.0f, Z = 1.0f, Z = comp->tex, Z = comp->r, Z = comp->g, Z = comp->b, Z = comp->a;
    Z = win_x2, Z = win_y1, Z = 1.0f, Z = 1.0f, Z = comp->tex, Z = comp->r, Z = comp->g, Z = comp->b, Z = comp->a;
    Z = win_x1, Z = win_y2, Z = 0.0f, Z = 0.0f, Z = comp->tex, Z = comp->r, Z = comp->g, Z = comp->b, Z = comp->a;
    Z = win_x2, Z = win_y2, Z = 1.0f, Z = 0.0f, Z = comp->tex, Z = comp->r, Z = comp->g, Z = comp->b, Z = comp->a;
    V = idx, V = idx + 1, V = idx + 2, V = idx + 2, V = idx + 1, V = idx + 3;
    gui_update_data_add_text(comp, new_x1, new_y1, new_x2 - new_x1, new_y2 - new_y1);
    for (i32 i = 0; i < comp->num_children; i++)
        gui_update_data_helper(comp->children[i], new_x1, new_y1, new_x2 - new_x1, new_y2 - new_y1);
}

void gui_update_data(void)
{
    gui.vbo_length = gui.ebo_length = 0;
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

void gui_update(void)
{
    gui_update_helper(comp_root, comp_root->x, comp_root->y, comp_root->w, comp_root->h);
    gui_update_data();
    if (gui.max_length_changed) {
        renderer_malloc(GUI_VAO, gui.vbo_max_length, gui.ebo_max_length);
        gui.max_length_changed = FALSE;
    }
    renderer_update(GUI_VAO, 0, gui.vbo_length, gui.vbo_buffer, 0, gui.ebo_length, gui.ebo_buffer);
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
    if (comp->interactable)
        component_key_callback(comp, key, scancode, action, mods);
}

void gui_key_callback(i32 key, i32 scancode, i32 action, i32 mods)
{
    gui_key_callback_helper(comp_root, comp_root->x, comp_root->y, comp_root->w, comp_root->h, key, scancode, action, mods);
}

void gui_destroy(void)
{
    component_destroy(comp_root);
    free(gui.vbo_buffer);
}