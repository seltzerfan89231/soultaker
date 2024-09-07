#include "../component.h"
#include <string.h>
#include <stdio.h>

#define WINDOW_FPS 0
#define GAME_FPS 1

void comp_textbox_create(Component *comp)
{
    component_set_text(comp, 14, "THE QUICK BROWN FOX JUMPED OVER THE LAZY DOG 0123456789");
}

void comp_textbox_destroy(Component *comp)
{
    
}

void comp_textbox_update(Component *comp)
{
    static f32 cooldown;
    if (glfwGetTime() - cooldown > 0.1) {
        component_destroy_children(comp);
        char text[100], num[20];
        strcpy(text, "WFPS ");
        sprintf(num, "%.0f", window.fps);
        strncat(text, num, 20);
        strncat(text, "\nGFPS ", 20);
        sprintf(num, "%d", (i32)(1.0 / game_dt));
        strncat(text, num, 20);
        strncat(text, "\nPROJ ", 20);
        sprintf(num, "%d", global_projectiles.length);
        strncat(text, num, 20);
        strncat(text, "\nPART ", 20);
        sprintf(num, "%d", global_particles.length + global_parjicles.length);
        strncat(text, num, 20);
        strncat(text, "\nHP   ", 20);
        sprintf(num, "%d/%d", (i32)player.health, (i32)player.max_health);
        strncat(text, num, 20);
        strncat(text, "\nMP   ", 20);
        sprintf(num, "%d/%d", (i32)player.mana, (i32)player.max_mana);
        strncat(text, num, 20);
        component_set_text(comp, 14, text);
        cooldown = glfwGetTime();
    }
}

void comp_textbox_mouse_button_callback(Component *comp, i32 button, i32 action)
{

}

void comp_textbox_key_callback(Component *comp, i32 key, i32 scancode, i32 action, i32 mods)
{

}

void comp_textbox_hover_callback(Component *comp, i32 action)
{

}
