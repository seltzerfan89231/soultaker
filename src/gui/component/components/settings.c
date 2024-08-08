#include "../component.h"

void comp_settings_update(Component *comp)
{

}

void comp_settings_mouse_button_callback(Component *comp, i32 button, i32 action)
{
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
        component_destroy_children(comp_root);
        Component *header = component_create(0, 0.9, 1.0, 0.1, EMPTY_TEX);
        header->r = 0.5;
        header->g = 0.7;
        header->b = 0.9;
        header->a = 1.0;
        component_attach(comp_root, header);
    }
}

void comp_settings_key_callback(Component *comp, i32 key, i32 scancode, i32 action, i32 mods)
{

}

void comp_settings_hover_callback(Component *comp, i32 action)
{
    
}