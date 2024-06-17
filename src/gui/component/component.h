#ifndef COMPONENT_H
#define COMPONENT_H

#include "../../util/type.h"

typedef struct Component Component;

typedef struct Component {
    f32 x, y, w, h, a, id;
    Component **children;
    u32 num_children;
    bool interactable;
} Component;

Component* component_create(f32 x, f32 y, f32 w, f32 h, f32 a, f32 id);
void component_attach(Component *parent, Component *child);
void component_detach(Component *parent, Component *child);
void component_destroy(Component *comp);

#endif