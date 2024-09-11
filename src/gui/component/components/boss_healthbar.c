#include "../component.h"

void comp_boss_healthbar_create(Component *comp)
{
    comp->a = 0.3;
}

void comp_boss_healthbar_update(Component *comp)
{
    Entity* boss = game_get_current_boss();
    if (boss != NULL) {
        char text[50];
        sprintf(text, "%d/%d\n", (i32)boss->health, (i32)boss->max_health);
        component_set_text(comp, 14, text);
    }
    else
        component_remove_text(comp);
}

void comp_boss_healthbar_destroy(Component *comp)
{
    
}

void comp_boss_healthbar_mouse_button_callback(Component *comp, i32 button, i32 action)
{

}

void comp_boss_healthbar_key_callback(Component *comp, i32 key, i32 scancode, i32 action, i32 mods)
{

}

void comp_boss_healthbar_hover_callback(Component *comp, i32 action)
{
    
}