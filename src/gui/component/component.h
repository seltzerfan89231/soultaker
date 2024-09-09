#ifndef COMPONENT_H
#define COMPONENT_H

#include "../../util/type.h"
#include "../../util/indices.h"
#include "../../window/window.h"
#include "../../game/game.h"
#include "../../audio/audio.h"
#include "character.h"

#define ALIGN_LEFT   0
#define ALIGN_TOP    0
#define ALIGN_RIGHT  1
#define ALIGN_DOWN   1
#define ALIGN_CENTER 2
#define JUSTIFY      3

typedef struct Component Component;

typedef struct Component {
    i32 x, y, w, h;
    f32 r, g, b, a;
    Component **children;
    u32 num_children, tex, id, sub_id, font_size;
    struct {
        u8 x, y;
    } alignment;
    bool interactable, hoverable, hovered, relative, update_children;
    char* text;
} Component;

extern Window window;
extern Component *comp_root;

Component* component_create(i32 x, i32 y, i32 w, i32 h, u32 id, u32 tex);
void component_attach(Component *parent, Component *child);
void component_detach(Component *parent, Component *child);
void component_destroy(Component *comp);
void component_detach_and_destroy(Component *comp, Component *child);
void component_destroy_children(Component *comp);

bool component_input_paused(void);
void component_pause_input(Component *comp, bool val);
void component_set_text(Component *comp, u8 font_size, char *text);
void component_remove_text(Component *comp);
void component_mouse_button_callback(Component *comp, i32 button, i32 action);
void component_key_callback(Component *comp, i32 key, i32 scancode, i32 action, i32 mods);
void component_update(Component *comp);
void component_hover_callback(Component *comp, i32 action);

#define HOVER_OFF 0
#define HOVER_ON  1

#define COMP_DEFAULT 0
#define COMP_BUTTON 1
#define COMP_ICON 2
#define COMP_HEALTHBAR 3
#define COMP_POPUP 4
#define COMP_TEXTBOX 5
#define COMP_SINGLEPLAYER 6
#define COMP_MULTIPLAYER 7
#define COMP_DEATH 8
#define COMP_MANABAR 9
#define COMP_HOST 10
#define COMP_JOIN 11
#define COMP_MINIMAP 12
#define COMP_CHAT 13

#define _COMP_INIT(_ltype) \
    void comp_##_ltype##_create(Component *comp); \
    void comp_##_ltype##_mouse_button_callback(Component *comp, i32 button, i32 action); \
    void comp_##_ltype##_hover_callback(Component *comp, i32 action); \
    void comp_##_ltype##_key_callback(Component *comp, i32 key, i32 scancode, i32 action, i32 mods); \
    void comp_##_ltype##_update(Component *comp); \
    void comp_##_ltype##_destroy(Component *comp);

_COMP_INIT(button)
_COMP_INIT(icon)
_COMP_INIT(healthbar)
_COMP_INIT(popup)
_COMP_INIT(textbox)
_COMP_INIT(singleplayer)
_COMP_INIT(multiplayer)
_COMP_INIT(death)
_COMP_INIT(manabar)
_COMP_INIT(host)
_COMP_INIT(join)
_COMP_INIT(minimap)
_COMP_INIT(chat)

#endif