#include "component.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

extern Window window;

static char char_map[128];

void component_init(void)
{
    char_map[' '] = NO_TEX;
    char_map['A'] = A_TEX;
    char_map['B'] = B_TEX;
    //char_map['C'] = C_TEX;
}

Component* component_create(f32 x, f32 y, f32 w, f32 h, f32 a, u32 id)
{
    Component *comp = malloc(sizeof(Component));
    comp->x = x;
    comp->y = y;
    comp->w = w;
    comp->h = h;
    comp->a = a;
    comp->id = id;
    comp->children = NULL;
    comp->num_children = 0;
    comp->interactable = 1;
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

void component_add_text(Component *comp, char *text, u32 font_size, f32 gw, f32 gh)
{
    f32 w = font_size / window.size.x / gw, h = font_size / window.size.y / gh;
    u32 length = strlen(text);
    for (i32 i = 0; i < length; i++) {
        Component *letter = component_create((w + 0.005 / gw) * i, 0.0f, w, h, 1.0f, char_map[text[i]]);
        component_attach(comp, letter);
    }
}