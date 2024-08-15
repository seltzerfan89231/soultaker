#include "../component.h"

static void create_buttons(Component *comp)
{
    component_destroy_children(comp_root);

    Component *host = component_create(window.aspect_ratio / 2 - 0.2, 0.7, 0.4, 0.4 * 2.0/3, EMPTY_TEX);
    host->a = 0.2;
    component_set_text(host, 14, "HOST");
    host->hoverable = TRUE;
    host->interactable = TRUE;
    host->id = COMP_HOST;
    component_attach(comp_root, host);

    Component *join = component_create(window.aspect_ratio / 2 - 0.2, 0.3, 0.4, 0.4 * 2.0/3, EMPTY_TEX);
    join->a = 0.2;
    component_set_text(join, 14, "JOIN");
    join->interactable = TRUE;
    join->id = COMP_JOIN;
    component_attach(comp_root, join);
}

void comp_multiplayer_update(Component *comp)
{

}

void comp_multiplayer_mouse_button_callback(Component *comp, i32 button, i32 action)
{
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) 
        create_buttons(comp);
}

void comp_multiplayer_key_callback(Component *comp, i32 key, i32 scancode, i32 action, i32 mods)
{

}

void comp_multiplayer_hover_callback(Component *comp, i32 action)
{
    
}