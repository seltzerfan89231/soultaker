#include "../component.h"
#include <stdio.h>

void comp_start_button_update(Component *comp)
{
    
}

void comp_start_button_mouse_button_callback(Component *comp, i32 button, i32 action)
{
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
        game_setup(1);
        component_destroy_children(comp_root);
        Component *text_box = component_create(0.02, 0.93, 0.3, 0.05, EMPTY_TEX);
        text_box->a = 0;
        text_box->id = COMP_TEXTBOX;
        text_box->sub_id = 0;
        component_set_text(text_box, 14, "THE QUICK BROWN FOX JUMPED OVER THE LAZY DOG 0123456789");
        component_attach(comp_root, text_box);
        Component *btn = component_create(0.05f, 0.05f, 0.1f, 0.1f, BUTTON_TEX);
        btn->interactable = TRUE;
        btn->hoverable = TRUE;
        btn->id = COMP_BUTTON;
        Component *icon = component_create(0.15, 0.15, 0.7, 0.7, SWORD_1_TEX);
        icon->id = COMP_ICON;
        Component *healthbar = component_create(0.3, 0.05, 0.2, 0.02, NO_TEX);
        healthbar->id = COMP_HEALTHBAR;
        Component *green_part = component_create(0.0, 0.0, 0.75, 1.0, EMPTY_TEX);
        green_part->g = 1.0, green_part->r = 0.0, green_part->b = 0.0;
        Component *red_part = component_create(0.75, 0.0, 0.25, 1.0, EMPTY_TEX);
        red_part->r = 1.0, red_part->g = red_part->b = 0.0;
        component_attach(comp_root, btn);
        component_attach(btn, icon);
        component_attach(comp_root, healthbar);
        component_attach(healthbar, green_part);
        component_attach(healthbar, red_part);
        //Component *death_messsage = component_create(0.4, 0.93, 0.3, 0.05, EMPTY_TEX);
    }
}

void comp_start_button_key_callback(Component *comp, i32 key, i32 scancode, i32 action, i32 mods)
{

}

void comp_start_button_hover_callback(Component *comp, i32 action)
{
    
}
