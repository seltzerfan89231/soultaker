#include "../component.h"
#include <stdio.h>

void comp_button_create(Component *comp)
{
    comp->interactable = TRUE;
    comp->hoverable = TRUE;
}

void comp_button_destroy(Component *comp)
{

}

void comp_button_update(Component *comp)
{

}

void comp_button_mouse_button_callback(Component *comp, i32 button, i32 action)
{

}

void comp_button_key_callback(Component *comp, i32 key, i32 scancode, i32 action, i32 mods)
{

}

void comp_button_hover_callback(Component *comp, i32 action)
{
    if (action == HOVER_ON) {
        Component *new_comp = component_create(0.0, 1.1, 1.0, 1.0, COMP_POPUP, COLOR_TEX);
        new_comp->r = 0.5;
        new_comp->hoverable = FALSE;
        component_set_text(new_comp, 14, "DESC");
        component_attach(comp, new_comp);
    } else {
        for (i32 i = 0; i < comp->num_children; i++)
            if (comp->children[i]->id == COMP_POPUP)
                component_detach_and_destroy(comp, comp->children[i]);
    }
}
