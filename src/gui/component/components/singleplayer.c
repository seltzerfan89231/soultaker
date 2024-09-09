#include "../component.h"
#include <stdio.h>

void comp_singleplayer_create(Component *comp)
{
    comp->a = 0.2;
    component_set_text(comp, 14, "SINGLEPLAYER");
    comp->alignment.x = ALIGN_CENTER;
    comp->alignment.y = ALIGN_CENTER;
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

        Component *text_box = component_create(0.02, 0.93, 0.3, 0.05, COMP_TEXTBOX, NO_TEX);
        component_attach(comp_root, text_box);

        Component *btn = component_create(0.05f, 0.05f, 0.1f, 0.1f, COMP_BUTTON, BUTTON_TEX);
        component_attach(comp_root, btn);

        Component *icon = component_create(0.15, 0.15, 0.7, 0.7, COMP_ICON, NO_TEX);
        component_attach(btn, icon);

        Component *healthbar = component_create(0.3, 0.07, 0.2, 0.02, COMP_HEALTHBAR, NO_TEX);
        component_attach(comp_root, healthbar);

        Component *manabar = component_create(0.3, 0.05, 0.2, 0.02, COMP_MANABAR, NO_TEX);
        component_attach(comp_root, manabar);

        Component *death_message = component_create(0.4, 0.93, 0.3, 0.05, COMP_DEATH, NO_TEX);
        component_attach(comp_root, death_message);

        Component *minimap = component_create(window.aspect_ratio - 0.3, 0.7, 0.25, 0.25, COMP_MINIMAP, MINIMAP_TEX);
        component_attach(comp_root, minimap);

        Component *chat = component_create(0, 0.18, 0.4, 0.5, COMP_CHAT, NO_TEX);
        component_attach(comp_root, chat);
    }
}

void comp_singleplayer_key_callback(Component *comp, i32 key, i32 scancode, i32 action, i32 mods)
{

}

void comp_singleplayer_hover_callback(Component *comp, i32 action)
{
    
}
