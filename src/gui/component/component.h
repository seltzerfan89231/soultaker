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
Component* component_create(f32 x, f32 y, f32 w, f32 h, u32 tex);
void component_attach(Component *parent, Component *child);
void component_detach(Component *parent, Component *child);
void component_destroy(Component *comp);
void component_detach_and_destroy(Component *comp, Component *child);

void component_add_text(Component *comp, char *text, u32 font_size, f32 gw, f32 gh);
void component_onclick(Component *comp);
void component_update(Component *comp);
void component_hover_on(Component *comp);
void component_hover_off(Component *comp);

#define COMP_DEFAULT 0
#define COMP_BUTTON 1
#define COMP_ICON 2
#define COMP_HEALTHBAR 3
#define COMP_HEALTHBAR_GREEN 4
#define COMP_HEALTHBAR_RED 5
#define COMP_POPUP 6

#define _COMP_INIT(_ltype) \
    void comp_##_ltype##_hover_on(Component *comp); \
    void comp_##_ltype##_hover_off(Component *comp); \
    void comp_##_ltype##_update(Component *comp);

_COMP_INIT(button)
_COMP_INIT(icon)
_COMP_INIT(healthbar)
_COMP_INIT(healthbar_green)
_COMP_INIT(healthbar_red)
_COMP_INIT(popup)

#endif