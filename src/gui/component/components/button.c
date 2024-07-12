#include "../component.h"

void comp_button_update(Component *comp)
{

}

void comp_button_hover_on(Component *comp)
{
    if (comp->hovered)
        return;
    comp->hovered = TRUE;
    Component *new_comp = component_create(0.0, 1.1, 1.0, 1.0, EMPTY_TEX);
    new_comp->r = 0.5;
    new_comp->id = COMP_POPUP;
    new_comp->hoverable = FALSE;
    component_attach(comp, new_comp);
}

void comp_button_hover_off(Component *comp)
{
    if (!comp->hovered)
        return;
    comp->hovered = FALSE;
    for (i32 i = 0; i < comp->num_children; i++)
        if (comp->children[i]->id == COMP_POPUP)
            component_detach_and_destroy(comp, comp->children[i]);
}