#ifndef COMPONENT_H
#define COMPONENT_H

#include "../../util/type.h"
#include "../../util/indices.h"
#include "../../window/window.h"
#include "../../game/game.h"

typedef struct Component Component;

typedef struct Component {
    f32 x, y, w, h, r, g, b, a;
    Component **children;
    u32 num_children, tex, id;
    bool interactable, hoverable, hovered, relative;
} Component;

extern Window window;

void char_map_init(void);
Component* component_create(f32 x, f32 y, f32 w, f32 h, f32 a, u32 tex);
void component_attach(Component *parent, Component *child);
void component_detach(Component *parent, Component *child);
void component_destroy(Component *comp);
void component_detach_and_destroy(Component *comp, Component *child);
void component_add_text(Component *comp, char *text, u32 font_size, f32 gw, f32 gh);

bool component_update(Component *comp);

void component_hover_event(Component *comp);
bool component_hover_on(Component *comp);
bool component_hover_off(Component *comp);

#endif