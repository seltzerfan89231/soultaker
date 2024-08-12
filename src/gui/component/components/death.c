#include "../component.h"

void comp_death_update(Component *comp)
{
    if (player.entity == NULL)
        comp->show_text = TRUE;
    else
        comp->show_text = FALSE;
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