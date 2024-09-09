#include "component.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

extern Window window;
Component *comp_root;
static bool input_paused;

#define _COMP_CREATE(_id, _lid) \
    case COMP_##_id : comp_##_lid##_create(comp); break;

Component* component_create(f32 x, f32 y, f32 w, f32 h, u32 id, u32 tex)
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
    comp->text = NULL;
    comp->alignment.x = ALIGN_LEFT;
    comp->alignment.y = ALIGN_TOP;
    comp->id = id;
    switch (comp->id) {
        _COMP_CREATE(BUTTON, button)
        _COMP_CREATE(CHAT, chat)
        _COMP_CREATE(DEATH, death)
        _COMP_CREATE(HEALTHBAR, healthbar)
        _COMP_CREATE(HOST, host)
        _COMP_CREATE(ICON, icon)
        _COMP_CREATE(JOIN, join)
        _COMP_CREATE(MANABAR, manabar)
        _COMP_CREATE(MINIMAP, minimap)
        _COMP_CREATE(MULTIPLAYER, multiplayer)
        _COMP_CREATE(POPUP, popup)
        _COMP_CREATE(SINGLEPLAYER, singleplayer)
        _COMP_CREATE(TEXTBOX, textbox)
        default: comp->id = COMP_DEFAULT;
    }
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

#define _COMP_DESTROY(_id, _lid) \
    case COMP_##_id : comp_##_lid##_destroy(comp); break;

void component_destroy(Component *comp)
{
    switch (comp->id) {
        _COMP_DESTROY(CHAT, chat)
    }
    for (i32 i = 0; i < comp->num_children; i++)
        component_destroy(comp->children[i]);
    free(comp->text);
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

bool component_input_paused(void)
{
    return input_paused;
}

void component_pause_input(Component *comp, bool val)
{
    input_paused = val;
}

void component_set_text(Component *comp, u8 font_size, char *text)
{
    u32 length;
    char *copied_text;
    free(comp->text);
    length = strlen(text);
    if (length == 0) {
        comp->text = NULL;
        return;
    }
    copied_text = malloc((length + 1) * sizeof(char));
    strncpy(copied_text, text, length + 1);
    comp->font_size = font_size;
    comp->text = copied_text;
}

void component_remove_text(Component *comp)
{
    if (comp->text == NULL) 
        return;
    free(comp->text);
    comp->text = NULL;
}

#define _COMP_MB_CALLBACK(_type, _ltype) \
    case COMP_##_type : comp_##_ltype##_mouse_button_callback(comp, button, action); break;

void component_mouse_button_callback(Component *comp, i32 button, i32 action)
{
    switch (comp->id) {
        _COMP_MB_CALLBACK(BUTTON, button)
        _COMP_MB_CALLBACK(ICON, icon)
        _COMP_MB_CALLBACK(HEALTHBAR, healthbar)
        _COMP_MB_CALLBACK(POPUP, popup)
        _COMP_MB_CALLBACK(TEXTBOX, textbox)
        _COMP_MB_CALLBACK(SINGLEPLAYER, singleplayer)
        _COMP_MB_CALLBACK(MULTIPLAYER, multiplayer)
        _COMP_MB_CALLBACK(DEATH, death)
        _COMP_MB_CALLBACK(MANABAR, manabar)
        _COMP_MB_CALLBACK(HOST, host)
        _COMP_MB_CALLBACK(JOIN, join)
        _COMP_MB_CALLBACK(MINIMAP, minimap)
        _COMP_MB_CALLBACK(CHAT, chat)
    }
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
        _COMP_UPDATE(SINGLEPLAYER, singleplayer)
        _COMP_UPDATE(MULTIPLAYER, multiplayer)
        _COMP_UPDATE(DEATH, death)
        _COMP_UPDATE(MANABAR, manabar)
        _COMP_UPDATE(HOST, host)
        _COMP_UPDATE(JOIN, join)
        _COMP_UPDATE(MINIMAP, minimap)
        _COMP_UPDATE(CHAT, chat)
    }
}

#define _COMP_HOVER_CALLBACK(_type, _ltype) \
    case COMP_##_type : comp_##_ltype##_hover_callback(comp, action); break;

void component_hover_callback(Component *comp, i32 action)
{
    if (action == HOVER_ON  &&  comp->hovered)
        return;
    if (action == HOVER_OFF && !comp->hovered)
        return;
    comp->hovered = action;
    switch (comp->id) {
        _COMP_HOVER_CALLBACK(BUTTON, button)
        _COMP_HOVER_CALLBACK(ICON, icon)
        _COMP_HOVER_CALLBACK(HEALTHBAR, healthbar)
        _COMP_HOVER_CALLBACK(POPUP, popup)
        _COMP_HOVER_CALLBACK(TEXTBOX, textbox)
        _COMP_HOVER_CALLBACK(SINGLEPLAYER, singleplayer)
        _COMP_HOVER_CALLBACK(MULTIPLAYER, multiplayer)
        _COMP_HOVER_CALLBACK(DEATH, death)
        _COMP_HOVER_CALLBACK(MANABAR, manabar)
        _COMP_HOVER_CALLBACK(HOST, host)
        _COMP_HOVER_CALLBACK(JOIN, join)
        _COMP_HOVER_CALLBACK(MINIMAP, minimap)
        _COMP_HOVER_CALLBACK(CHAT, chat)
    }
}

#define _COMP_KEY_CALLBACK(_type, _ltype) \
    case COMP_##_type : comp_##_ltype##_key_callback(comp, key, scancode, action, mods); break;

void component_key_callback(Component *comp, i32 key, i32 scancode, i32 action, i32 mods)
{
    switch (comp->id) {
        _COMP_KEY_CALLBACK(BUTTON, button)
        _COMP_KEY_CALLBACK(ICON, icon)
        _COMP_KEY_CALLBACK(HEALTHBAR, healthbar)
        _COMP_KEY_CALLBACK(POPUP, popup)
        _COMP_KEY_CALLBACK(TEXTBOX, textbox)
        _COMP_KEY_CALLBACK(SINGLEPLAYER, singleplayer)
        _COMP_KEY_CALLBACK(MULTIPLAYER, multiplayer)
        _COMP_KEY_CALLBACK(DEATH, death)
        _COMP_KEY_CALLBACK(MANABAR, manabar)
        _COMP_KEY_CALLBACK(HOST, host)
        _COMP_KEY_CALLBACK(JOIN, join)
        _COMP_KEY_CALLBACK(MINIMAP, minimap)
        _COMP_KEY_CALLBACK(CHAT, chat)
    }
}