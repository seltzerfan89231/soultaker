#include "../component.h"
#include <stdio.h>

void comp_minimap_create(Component *comp)
{
    comp->interactable = TRUE;
    comp->a = 0.0;
}

void comp_minimap_destroy(Component *comp)
{
    
}

void comp_minimap_update(Component *comp)
{
    
}

void comp_minimap_mouse_button_callback(Component *comp, i32 button, i32 action)
{

}

void comp_minimap_key_callback(Component *comp, i32 key, i32 scancode, i32 action, i32 mods)
{
    if (key == GLFW_KEY_TAB && action == GLFW_PRESS)
        comp->a = 0.5;
    if (key == GLFW_KEY_TAB && action == GLFW_RELEASE)
        comp->a = 0;
}

void comp_minimap_hover_callback(Component *comp, i32 action)
{
    
}