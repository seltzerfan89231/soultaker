#include "../component.h"

void comp_healthbar_update(Component *comp)
{
    Component *green_part, *red_part;
    green_part = comp->children[0];
    red_part = comp->children[1];
    green_part->w = game_get_player_health_ratio();
    red_part->w = 1 - green_part->w;
    red_part->x = green_part->w;
}

void comp_healthbar_hover_on(Component *comp)
{
    
}

void comp_healthbar_hover_off(Component *comp)
{
    
}