#include "component.h"
#include <stdlib.h>

Component* component_create(f32 x, f32 y, f32 w, f32 h, f32 a, f32 id)
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