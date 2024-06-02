#include "component.h"
#include <stdlib.h>

Component* component_create(f32 x1, f32 y1, f32 x2, f32 y2, f32 r, f32 g, f32 b, f32 a)
{
    Component *comp = malloc(sizeof(Component));
    comp->x1 = x1; comp->x2 = x2;
    comp->y1 = y1; comp->y2 = y2;
    comp->r = r; comp->g = g; comp->b = b; comp->a = a;
    comp->children = NULL;
    comp->num_children = 0;
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