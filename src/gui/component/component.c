#include "component.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

extern Window window;

static char char_map[128];

void char_map_init(void)
{
    char_map[' '] = NO_TEX;
    char_map['0'] = NUM_0_TEX;
    char_map['1'] = NUM_1_TEX;
    char_map['2'] = NUM_2_TEX;
    char_map['3'] = NUM_3_TEX;
    char_map['4'] = NUM_4_TEX;
    char_map['5'] = NUM_5_TEX;
    char_map['6'] = NUM_6_TEX;
    char_map['7'] = NUM_7_TEX;
    char_map['8'] = NUM_8_TEX;
    char_map['9'] = NUM_9_TEX;
    char_map['A'] = A_TEX;
    char_map['B'] = B_TEX;
    char_map['C'] = C_TEX;
    char_map['D'] = D_TEX;
    char_map['E'] = E_TEX;
    char_map['F'] = F_TEX;
    char_map['G'] = G_TEX;
    char_map['H'] = H_TEX;
    char_map['I'] = I_TEX;
    char_map['J'] = J_TEX;
    char_map['K'] = K_TEX;
    char_map['L'] = L_TEX;
    char_map['M'] = M_TEX;
    char_map['N'] = N_TEX;
    char_map['O'] = O_TEX;
    char_map['P'] = P_TEX;
    char_map['Q'] = Q_TEX;
    char_map['R'] = R_TEX;
    char_map['S'] = S_TEX;
    char_map['T'] = T_TEX;
    char_map['U'] = U_TEX;
    char_map['V'] = V_TEX;
    char_map['W'] = W_TEX;
    char_map['X'] = X_TEX;
    char_map['Y'] = Y_TEX;
    char_map['Z'] = Z_TEX;
}

Component* component_create(f32 x, f32 y, f32 w, f32 h, u32 tex)
{
    Component *comp = malloc(sizeof(Component));
    comp->x = x, comp->y = y, comp->w = w, comp->h = h;
    comp->r = comp->g = comp->b = comp->a = 1.0f;
    comp->tex = tex;
    comp->children = NULL;
    comp->num_children = 0;
    comp->interactable = TRUE;
    comp->hoverable = TRUE;
    comp->hovered = FALSE;
    comp->relative = TRUE;
    comp->id = 0;
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

void component_add_text(Component *comp, char *text, u32 font_size, f32 gw, f32 gh)
{
    f32 w = (f32)font_size / window.width / gw, h = (f32)font_size / window.height / gh;
    u32 length = strlen(text);
    for (i32 i = 0; i < length; i++) {
        Component *letter = component_create((w + 0.005 / gw) * i, 0, w, h, char_map[text[i]]);
        letter->r = letter->g = letter->b = 0.0f;
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
        _COMP_UPDATE(HEALTHBAR_GREEN, healthbar_green)
        _COMP_UPDATE(HEALTHBAR_RED, healthbar_red)
        _COMP_UPDATE(POPUP, popup)
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
        _COMP_HOVER_ON(HEALTHBAR_GREEN, healthbar_green)
        _COMP_HOVER_ON(HEALTHBAR_RED, healthbar_red)
        _COMP_HOVER_ON(POPUP, popup)
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
        _COMP_HOVER_OFF(HEALTHBAR_GREEN, healthbar_green)
        _COMP_HOVER_OFF(HEALTHBAR_RED, healthbar_red)
        _COMP_HOVER_OFF(POPUP, popup)
    }
}