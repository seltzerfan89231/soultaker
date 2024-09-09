#include "gui.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../util/extlib.h"

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
    
    comp_root = component_create(0.0f, 0.0f, DEFAULT_WINDOW_WIDTH, DEFAULT_WINDOW_HEIGHT, COMP_DEFAULT, NO_TEX);
    comp_root->a = 0;
    gui.max_length_changed = TRUE;

    component_attach(comp_root, component_create(480 - 75, 270 - 50, 150, 100, COMP_SINGLEPLAYER, COLOR_TEX));
    component_attach(comp_root, component_create(480 - 75, 100, 150, 100, COMP_MULTIPLAYER, COLOR_TEX));
    Component *comp = component_create(20, 20, 250, 250, COMP_DEFAULT, COLOR_TEX);
    //comp->alignment.x = ALIGN_RIGHT;
    //comp->alignment.y = ALIGN_CENTER;
    comp->a = 0.3;
    component_set_text(comp, 14, "aaaaaaaaaaaaaaaaaaaaaaaaaaaa");
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

static i32 get_num_lines(Component *comp)
{
    f32 fs, gs, px, py, bx, by, ox, oy, lx, ly, lw, lh, adv;
    i32 length, left, right, right_copy, nl;
    char *text = comp->text;
    length = strlen(text);
    fs = comp->font_size / GLYPH_HEIGHT;
    gs = fs * GLYPH_HEIGHT;
    px = fs;
    py = fs * (2 - MIN_BEARING_Y);
    nl = 0;
    while (right < length) {
        f32 test_ox = -px;
        while (left != 0 && right < length && text[right] == ' ' || text[right] == '\t')
            right++;
        left = right;
        while (right < length && text[right] != '\n' && test_ox <= comp->w) {
            if (text[right] == '\r') {
                right++;
                while (right < length && text[right] != '\r')
                    right++;
                right++;
                continue;
            }
            Character c = char_map[text[right]];
            test_ox += fs * c.advance + px;
            right++;
        }
        if (right < length && text[right] == '\n')
            right++;
        right_copy = (test_ox > comp->w && right > left + 1) ? right - 1 : right;
        if (test_ox > comp->w) {
            while (right > left && text[right-1] != ' ' && text[right-1] != '\t') {
                if (text[right-1] == '\r') {
                    right--;
                    while (right > left && text[right-1] != '\r')
                        right--;
                    right--;
                    continue;
                }
                Character c = char_map[text[right-1]];
                test_ox -= fs * c.advance + px;
                right--;
            }
            while (right > left && (text[right-1] == ' ' || text[right-1] == '\t')) { 
                right--;
                Character c = char_map[text[right]];
                test_ox -= fs * c.advance + px;
            } 
        }
        if (left == right)
            right = right_copy;
        ox = 0;
        right = (right > length) ? length : right;
        while (left < right) {
            if (text[left] == '\n') {
                left++;
                continue;
            } else if (text[left] == '\r') {
                left++;
                while (left < right && text[left] != '\r')
                    left++;
                left++;
                continue;
            }
            Character c = char_map[text[left]];
            lw = fs * c.size.x;
            lh = fs * c.size.y;
            bx = fs * c.bearing.x;
            by = fs * c.bearing.y;
            adv = fs * c.advance;
            lx = ox + bx;
            ly = comp->h - gs + by - oy;
            ox += adv + px;
            left++;
        }
        oy += gs + py;
        nl++;
    }
    return nl;
}

static void update_text_data(Component *comp, i32 x, i32 y)
{
    i32 new_x1, new_y1, new_x2, new_y2;
    f32 win_x1, win_x2, win_y1, win_y2;
    i32 fs, gs, tr, tb, tg, th, px, py, bx, by, ox, oy, lx, ly, lw, lh, adv;
    i32 nl, length, left, right, right_copy;
    char *text = comp->text;
    length = strlen(text);
    fs = comp->font_size / GLYPH_HEIGHT;
    gs = fs * GLYPH_HEIGHT;
    px = fs;
    py = fs * (2 - MIN_BEARING_Y);
    oy = 0;
    tr = tb = tg = 1.0f;
    nl = (comp->alignment.y != ALIGN_TOP) ? get_num_lines(comp) : 0;
    th = nl * gs + (nl - 1) * py;
    if (comp->alignment.y == ALIGN_CENTER)
        oy = (comp->h - th) / 2;
    else if (comp->alignment.y == ALIGN_DOWN)
        oy = comp->h - th;
    left = right = 0;
    while (right < length) {
        f32 test_ox = -px;
        while (left != 0 && right < length && text[right] == ' ' || text[right] == '\t')
            right++;
        left = right;
        while (right < length && text[right] != '\n' && test_ox <= comp->w) {
            if (right < length && text[right] == '\r') {
                right++;
                while (right < length && text[right] != '\r')
                    right++;
                right++;
                continue;
            }
            Character c = char_map[text[right]];
            test_ox += fs * c.advance + px;
            right++;
        }
        if (right < length && text[right] == '\n')
            right++;
        right_copy = (test_ox > comp->w && right > left + 1) ? right - 1 : right;
        if (test_ox > comp->w) {
            while (right > left && text[right-1] != ' ' && text[right-1] != '\t') {
                if (right > left && text[right-1] == '\r') {
                    right--;
                    while (right > left && text[right-1] != '\r')
                        right--;
                    right--;
                    continue;
                }
                Character c = char_map[text[right-1]];
                test_ox -= fs * c.advance + px;
                right--;
            }
            while (right > left && (text[right-1] == ' ' || text[right-1] == '\t')) { 
                Character c = char_map[text[right-1]];
                test_ox -= fs * c.advance + px;
                right--;
            } 
        }
        if (left == right)
            right = right_copy;
        ox = 0;
        if (comp->alignment.x == ALIGN_CENTER)
            ox = (comp->w - test_ox) / 2.0;
        else if (comp->alignment.x == ALIGN_RIGHT)
            ox = comp->w - test_ox;
        right = (right > length) ? length : right;
        while (left < right) {
            if (text[left] == '\n') {
                left++;
                continue;
            } else if (text[left] == '\r') {
                if (isxnumber(text + left + 1, 6)) {
                    tr = (atox(text[left+1]) << 4 + atox(text[left+2])) / 255.0;
                    tg = (atox(text[left+3]) << 4 + atox(text[left+4])) / 255.0;
                    tb = (atox(text[left+5]) << 4 + atox(text[left+6])) / 255.0;
                }
                left++;
                while (left < right && text[left] != '\r')
                    left++;
                left++;
                continue;
            }
            Character c = char_map[text[left]];
            lw = fs * c.size.x;
            lh = fs * c.size.y;
            bx = fs * c.bearing.x;
            by = fs * c.bearing.y;
            adv = fs * c.advance;
            lx = ox + bx;
            ly = comp->h - gs + by - oy;
            ox += adv + px;
            new_x1 = lx + x, new_x2 = lx + lw + x;
            new_y1 = ly + y, new_y2 = ly + lh + y;
            win_x1 = 2 * ((f32)new_x1 / DEFAULT_WINDOW_WIDTH - 0.5f), win_y1 = 2 * ((f32)new_y1 / DEFAULT_WINDOW_HEIGHT - 0.5f);
            win_x2 = 2 * ((f32)new_x2 / DEFAULT_WINDOW_WIDTH - 0.5f), win_y2 = 2 * ((f32)new_y2 / DEFAULT_WINDOW_HEIGHT - 0.5f);
            u32 idx = gui.vbo_length / 9;
            if (text[left] != ' ' && text[left] != '\t') {
                Z = win_x1, Z = win_y1, Z = 0.0f, Z = 1.0f, Z = c.tex, Z = tr, Z = tg, Z = tb, Z = 1.0f;
                Z = win_x2, Z = win_y1, Z = 1.0f, Z = 1.0f, Z = c.tex, Z = tr, Z = tg, Z = tb, Z = 1.0f;
                Z = win_x1, Z = win_y2, Z = 0.0f, Z = 0.0f, Z = c.tex, Z = tr, Z = tg, Z = tb, Z = 1.0f;
                Z = win_x2, Z = win_y2, Z = 1.0f, Z = 0.0f, Z = c.tex, Z = tr, Z = tg, Z = tb, Z = 1.0f;
                V = idx, V = idx + 1, V = idx + 2, V = idx + 2, V = idx + 1, V = idx + 3;
            }
            left++;
        }
        oy += gs + py;
    }
}

void gui_update_data_add_text(Component *comp, i32 x, i32 y)
{
    if (comp->text == NULL)
        return;
    resize_gui_buffers(strlen(comp->text));
    update_text_data(comp, x, y);
}

void gui_update_data_helper(Component *comp, i32 x, i32 y)
{
    i32 new_x1, new_y1, new_x2, new_y2;
    f32 win_x1, win_x2, win_y1, win_y2;
    if (comp->relative) {
        new_x1 = comp->x + x, new_x2 = comp->x + comp->w + x;
        new_y1 = comp->y + y, new_y2 = comp->y + comp->h + y;
    } else {
        new_x1 = comp->x, new_x2 = comp->x + comp->w;
        new_y1 = comp->y, new_y2 = comp->y + comp->h;
    }
    win_x1 = 2 * ((f32)new_x1 / DEFAULT_WINDOW_WIDTH - 0.5f), win_y1 = 2 * ((f32)new_y1 / DEFAULT_WINDOW_HEIGHT - 0.5f);
    win_x2 = 2 * ((f32)new_x2 / DEFAULT_WINDOW_WIDTH - 0.5f), win_y2 = 2 * ((f32)new_y2 / DEFAULT_WINDOW_HEIGHT - 0.5f);
    resize_gui_buffers(1);
    u32 idx = gui.vbo_length / 9;
    Z = win_x1, Z = win_y1, Z = 0.0f, Z = 1.0f, Z = comp->tex, Z = comp->r, Z = comp->g, Z = comp->b, Z = comp->a;
    Z = win_x2, Z = win_y1, Z = 1.0f, Z = 1.0f, Z = comp->tex, Z = comp->r, Z = comp->g, Z = comp->b, Z = comp->a;
    Z = win_x1, Z = win_y2, Z = 0.0f, Z = 0.0f, Z = comp->tex, Z = comp->r, Z = comp->g, Z = comp->b, Z = comp->a;
    Z = win_x2, Z = win_y2, Z = 1.0f, Z = 0.0f, Z = comp->tex, Z = comp->r, Z = comp->g, Z = comp->b, Z = comp->a;
    V = idx, V = idx + 1, V = idx + 2, V = idx + 2, V = idx + 1, V = idx + 3;
    gui_update_data_add_text(comp, new_x1, new_y1);
    for (i32 i = 0; i < comp->num_children; i++)
        gui_update_data_helper(comp->children[i], new_x1, new_y1);
}

void gui_update_data(void)
{
    gui.vbo_length = gui.ebo_length = 0;
    gui_update_data_helper(comp_root, comp_root->x, comp_root->y);
}

static bool cursor_in_bounds(i32 x1, i32 x2, i32 y1, i32 y2)
{
    return window.cursor.position.x * DEFAULT_WINDOW_WIDTH >= x1 
           && window.cursor.position.x * DEFAULT_WINDOW_WIDTH <= x2 
           && DEFAULT_WINDOW_HEIGHT * (1 - window.cursor.position.y) >= y1 
           && DEFAULT_WINDOW_HEIGHT * (1 - window.cursor.position.y) <= y2;
}

void gui_update_helper(Component *comp, i32 x, i32 y)
{
    i32 new_x1, new_y1, new_x2, new_y2;
    if (comp->relative) {
        new_x1 = comp->x + x, new_x2 = comp->x + comp->w + x;
        new_y1 = comp->y + y, new_y2 = comp->y + comp->h + y;
    } else {
        new_x1 = comp->x, new_x2 = comp->x + comp->w;
        new_y1 = comp->y, new_y2 = comp->y + comp->h;
    }
    if (comp->update_children)
        for (i32 i = 0; i < comp->num_children; i++)
            gui_update_helper(comp->children[i], new_x1, new_y1);
    component_update(comp);
    if (!comp->hoverable)
        return;
    component_hover_callback(comp, cursor_in_bounds(new_x1, new_x2, new_y1, new_y2));
}

void gui_update(void)
{
    gui_update_helper(comp_root, comp_root->x, comp_root->y);
    gui_update_data();
    if (gui.max_length_changed) {
        renderer_malloc(GUI_VAO, gui.vbo_max_length, gui.ebo_max_length);
        gui.max_length_changed = FALSE;
    }
    renderer_update(GUI_VAO, 0, gui.vbo_length, gui.vbo_buffer, 0, gui.ebo_length, gui.ebo_buffer);
}

void gui_mouse_button_callback_helper(Component *comp, i32 x, i32 y, i32 button, i32 action)
{
    i32 new_x1, new_y1, new_x2, new_y2;
    if (comp->relative) {
        new_x1 = comp->x + x, new_x2 = comp->x + comp->w + x;
        new_y1 = comp->y + y, new_y2 = comp->y + comp->h + y;
    } else {
        new_x1 = comp->x, new_x2 = comp->x + comp->w;
        new_y1 = comp->y, new_y2 = comp->y + comp->h;
    }
    if (comp->update_children)
        for (i32 i = 0; i < comp->num_children; i++)
            gui_mouse_button_callback_helper(comp->children[i], new_x1, new_y1, button, action);
    if (comp->interactable && cursor_in_bounds(new_x1, new_x2, new_y1, new_y2))
        component_mouse_button_callback(comp, button, action);
}

void gui_mouse_button_callback(i32 button, i32 action)
{
    gui_mouse_button_callback_helper(comp_root, comp_root->x, comp_root->y, button, action);
}

void gui_key_callback_helper(Component *comp, i32 x, i32 y, i32 key, i32 scancode, i32 action, i32 mods)
{
    f32 new_x1, new_y1, new_x2, new_y2;
    if (comp->relative) {
        new_x1 = comp->x + x, new_x2 = comp->x + comp->w + x;
        new_y1 = comp->y + y, new_y2 = comp->y + comp->h + y;
    } else {
        new_x1 = comp->x, new_x2 = comp->x + comp->w;
        new_y1 = comp->y, new_y2 = comp->y + comp->h;
    }
    if (comp->update_children)
        for (i32 i = 0; i < comp->num_children; i++)
            gui_key_callback_helper(comp->children[i], new_x1, new_y1, key, scancode, action, mods);
    if (comp->interactable)
        component_key_callback(comp, key, scancode, action, mods);
}

void gui_key_callback(i32 key, i32 scancode, i32 action, i32 mods)
{
    gui_key_callback_helper(comp_root, comp_root->x, comp_root->y, key, scancode, action, mods);
}

void gui_destroy(void)
{
    component_destroy(comp_root);
    free(gui.vbo_buffer);
}