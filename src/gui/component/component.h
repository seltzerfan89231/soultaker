#ifndef COMPONENT_H
#define COMPONENT_H

#include "../../util/type.h"

typedef struct Component Component;

typedef struct Component {
    f32 x1, x2, y1, y2, r, g, b, a;
    Component **children;
    u32 num_children;
    bool interactable;
} Component;

Component* component_create(f32 x1, f32 y1, f32 x2, f32 y2, f32 r, f32 g, f32 b, f32 a);
void component_attach(Component *parent, Component *child);
void component_detach(Component *parent, Component *child);
void component_destroy(Component *comp);

#endif