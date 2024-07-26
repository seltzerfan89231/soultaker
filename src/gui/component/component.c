#include "component.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

extern Window window;
Component *comp_root;

Component* component_create(f32 x, f32 y, f32 w, f32 h, u32 tex)
{
    Component *comp = malloc(sizeof(Component));
    comp->x = x, comp->y = y, comp->w = w, comp->h = h;
    comp->r = comp->g = comp->b = comp->a = 1.0f;
    comp->tex = tex;
    comp->children = NULL;
    comp->num_children = 0;
    comp->interactable = FALSE;
    comp->hoverable = FALSE;
    comp->hovered = FALSE;
    comp->relative = TRUE;
    comp->update_children = TRUE;
    comp->id = COMP_DEFAULT;
    return comp;
}

void component_attach(Component *parent, Component *child)
{
    parent->num_children++;
    parent->children = realloc(parent->children, parent->num_children * sizeof(Component*));
    parent->children[parent->num_children-1] = child;
}

void component_detach(Component *parent, Component *child)
{
    for (i32 i = 0; i < parent->num_children; i++) {
        if (parent->children[i] == child) {
            parent->children[i] = parent->children[parent->num_children-1];
            parent->num_children--;
            parent->children = realloc(parent->children, parent->num_children * sizeof(Component*));
        }
    }
}

void component_destroy(Component *comp)
{
    for (i32 i = 0; i < comp->num_children; i++)
        component_destroy(comp->children[i]);
    free(comp->children);
    free(comp);
}

void component_detach_and_destroy(Component *comp, Component *child)
{
    component_detach(comp, child);
    component_destroy(child);
}

void component_destroy_children(Component *comp)
{
    while (comp->num_children != 0)
        component_detach_and_destroy(comp, comp->children[0]);
}

void component_add_text(Component *comp, char *text, u32 font_size, f32 gw, f32 gh)
{
    /*                    padding  bearing  origin */
    f32 pixel_size, w, h, px, py,  bx, by,  ox, oy, adv;
    u32 length, i;
    pixel_size = (f32)font_size / (DEFAULT_WINDOW_HEIGHT);
    px = pixel_size * 2 / gw;
    py = pixel_size * 0.5 / gh;
    length = strlen(text);
    ox = oy = 0;
    for (i = 0; i < length; i++) {
        Character c = char_map[text[i]];
        w = pixel_size / gw * c.size.x / c.size.y;
        h = pixel_size / gh;
        bx = pixel_size * c.bearing.x / gw;
        by = pixel_size * c.bearing.y / gh;
        adv = pixel_size * c.advance / gw;
        printf("%c, %f\n", text[i], adv);
        if (text[i] != ' ' && ox + adv > 1)
            ox = 0, oy += h + py;
        Component *letter = component_create(ox + bx, 1 - h - by - oy, w, h, c.tex);
        ox += adv;
        letter->r = letter->g = letter->b = 1.0f;
        component_attach(comp, letter);
    }
}

void component_onclick(Component *comp)
{
    puts("Clicked!");
}

#define _COMP_UPDATE(_type, _ltype) \
    case COMP_##_type : comp_##_ltype##_update(comp); break;

void component_update(Component *comp)
{
    switch (comp->id) {
        _COMP_UPDATE(BUTTON, button)
        _COMP_UPDATE(ICON, icon)
        _COMP_UPDATE(HEALTHBAR, healthbar)
        _COMP_UPDATE(POPUP, popup)
        _COMP_UPDATE(TEXTBOX, textbox)
    }
}

#define _COMP_HOVER_ON(_type, _ltype) \
    case COMP_##_type : comp_##_ltype##_hover_on(comp); break;

void component_hover_on(Component *comp)
{
    switch (comp->id) {
        _COMP_HOVER_ON(BUTTON, button)
        _COMP_HOVER_ON(ICON, icon)
        _COMP_HOVER_ON(HEALTHBAR, healthbar)
        _COMP_HOVER_ON(POPUP, popup)
        _COMP_HOVER_ON(TEXTBOX, textbox)
    }
}

#define _COMP_HOVER_OFF(_type, _ltype) \
    case COMP_##_type : comp_##_ltype##_hover_off(comp); break;

void component_hover_off(Component *comp)
{
    switch (comp->id) {
        _COMP_HOVER_OFF(BUTTON, button)
        _COMP_HOVER_OFF(ICON, icon)
        _COMP_HOVER_OFF(HEALTHBAR, healthbar)
        _COMP_HOVER_OFF(POPUP, popup)
        _COMP_HOVER_OFF(TEXTBOX, textbox)
    }
}