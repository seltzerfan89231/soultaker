#include "../component.h"

void comp_death_update(Component *comp)
{
    if (player.entity == NULL)
        component_set_text(comp, 14, "YOU DIED");
    else
        component_remove_text(comp);
}

void comp_death_mouse_button_callback(Component *comp, i32 button, i32 action)
{

}

void comp_death_key_callback(Component *comp, i32 key, i32 scancode, i32 action, i32 mods)
{

}

void comp_death_hover_callback(Component *comp, i32 action)
{
    
}