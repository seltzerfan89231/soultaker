#include "../component.h"
#include <stdio.h>

void comp_singleplayer_create(Component *comp)
{
    comp->a = 0.2;
    component_set_text(comp, 14, "SINGLEPLAYER");
    //comp->alignment.x = ALIGN_CENTER;
    //comp->alignment.y = ALIGN_CENTER;
    comp->hoverable = TRUE;
    comp->interactable = TRUE;
}

void comp_singleplayer_destroy(Component *comp)
{
    
}

void comp_singleplayer_update(Component *comp)
{
    
}

void comp_singleplayer_mouse_button_callback(Component *comp, i32 button, i32 action)
{
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
        audio_play_sound(GUI_CLICK_AUD);
        game_setup(4);
        component_destroy_children(comp_root);

        Component *text_box = component_create(10, 480, 150, 50, COMP_TEXTBOX, NO_TEX);
        component_attach(comp_root, text_box);

        Component *btn = component_create(10, 10, 80, 80, COMP_BUTTON, BUTTON_TEX);
        component_attach(comp_root, btn);

        Component *icon = component_create(10, 10, 60, 60, COMP_ICON, NO_TEX);
        component_attach(btn, icon);

        Component *healthbar = component_create(100, 30, 100, 14, COMP_HEALTHBAR, NO_TEX);
        component_attach(comp_root, healthbar);

        Component *manabar = component_create(100, 16, 100, 14, COMP_MANABAR, NO_TEX);
        component_attach(comp_root, manabar);

        Component *death_message = component_create(155, 520, 50, 12, COMP_DEATH, NO_TEX);
        component_attach(comp_root, death_message);

        Component *minimap = component_create(790, 370, 150, 150, COMP_MINIMAP, MINIMAP_TEX);
        component_attach(comp_root, minimap);

        Component *chat = component_create(10, 120, 200, 100, COMP_CHAT, NO_TEX);
        component_attach(comp_root, chat);

        Component *boss_healthbar = component_create(10, 400, 80, 20, COMP_BOSS_HEALTHBAR, COLOR_TEX);
        component_attach(comp_root, boss_healthbar);
    }
}

void comp_singleplayer_key_callback(Component *comp, i32 key, i32 scancode, i32 action, i32 mods)
{

}

void comp_singleplayer_hover_callback(Component *comp, i32 action)
{
    
}
