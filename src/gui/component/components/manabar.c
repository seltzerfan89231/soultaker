#include "../component.h"

void comp_manabar_update(Component *comp)
{
    Component *green_part, *red_part;
    green_part = comp->children[0];
    red_part = comp->children[1];
    green_part->w = game_get_player_mana_ratio();
    red_part->w = 1 - green_part->w;
    red_part->x = green_part->w;
}

void comp_manabar_mouse_button_callback(Component *comp, i32 button, i32 action)
{

}

void comp_manabar_key_callback(Component *comp, i32 key, i32 scancode, i32 action, i32 mods)
{

}

void comp_manabar_hover_callback(Component *comp, i32 action)
{
    
}