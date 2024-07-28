#include "../component.h"

void comp_icon_update(Component *comp)
{
    comp->tex = game_get_weapon_tex();
}

void comp_icon_mouse_button_callback(Component *comp, i32 button, i32 action)
{

}

void comp_icon_key_callback(Component *comp, i32 key, i32 scancode, i32 action, i32 mods)
{

}

void comp_icon_hover_callback(Component *comp, i32 action)
{
    
}