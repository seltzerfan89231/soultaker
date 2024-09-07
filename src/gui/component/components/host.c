#include "../component.h"
#include "../../../networking/networking.h"

static void create_buttons(Component *comp)
{
    component_destroy_children(comp_root);
    Component *waiting = component_create(window.aspect_ratio / 2 - 0.2, 0.7, 0.4, 0.4 * 2.0/3, COMP_DEFAULT, COLOR_TEX);
    waiting->a = 0.2;
    component_set_text(waiting, 14, "Waiting");
    waiting->hoverable = TRUE;
    waiting->interactable = TRUE;
    component_attach(comp_root, waiting);
}

void comp_host_create(Component *comp)
{
    comp->a = 0.2;
    component_set_text(comp, 14, "HOST");
    comp->hoverable = TRUE;
    comp->interactable = TRUE;
}

void comp_host_destroy(Component *comp)
{
    
}

void comp_host_update(Component *comp)
{
    
}

void comp_host_mouse_button_callback(Component *comp, i32 button, i32 action)
{
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
        networking_host();
        create_buttons(comp);
    }
}

void comp_host_key_callback(Component *comp, i32 key, i32 scancode, i32 action, i32 mods)
{

}

void comp_host_hover_callback(Component *comp, i32 action)
{
    
}