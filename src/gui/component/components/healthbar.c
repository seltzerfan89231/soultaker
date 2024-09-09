#include "../component.h"

void comp_healthbar_create(Component *comp)
{
    Component *green_part = component_create(0, 0, 0, 14, COMP_DEFAULT, COLOR_TEX);
    green_part->g = 1.0, green_part->r = 0.0, green_part->b = 0.0;
    Component *red_part = component_create(0, 0, 0, 14, COMP_DEFAULT, COLOR_TEX);
    red_part->r = 1.0, red_part->g = 0.0, red_part->b = 0.0;
    component_attach(comp, green_part);
    component_attach(comp, red_part);
}

void comp_healthbar_destroy(Component *comp)
{
    
}

void comp_healthbar_update(Component *comp)
{
    Component *green_part, *red_part;
    green_part = comp->children[0];
    red_part = comp->children[1];
    green_part->w = game_get_player_health_ratio() * 100;
    red_part->w = 100 - green_part->w;
    red_part->x = green_part->w;
}

void comp_healthbar_mouse_button_callback(Component *comp, i32 button, i32 action)
{

}

void comp_healthbar_key_callback(Component *comp, i32 key, i32 scancode, i32 action, i32 mods)
{

}

void comp_healthbar_hover_callback(Component *comp, i32 action)
{
    
}