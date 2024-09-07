#include "../component.h"

void comp_manabar_create(Component *comp)
{
    Component *blue_part = component_create(0.0, 0.0, 0.75, 1.0, COMP_DEFAULT, COLOR_TEX);
    blue_part->g = 0.0, blue_part->r = 0.0, blue_part->b = 1.0;
    Component *yellow_part = component_create(0.75, 0.0, 0.25, 1.0, COMP_DEFAULT, COLOR_TEX);
    yellow_part->r = 1.0, yellow_part->g = 1.0, yellow_part->b = 0.0;
    component_attach(comp, blue_part);
    component_attach(comp, yellow_part);
}

void comp_manabar_destroy(Component *comp)
{
    
}

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