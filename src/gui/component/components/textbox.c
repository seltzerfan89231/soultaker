#include "../component.h"
#include <string.h>
#include <stdio.h>

#define WINDOW_FPS 0
#define GAME_FPS 1

void comp_textbox_update(Component *comp)
{
    return;
    static f32 cooldown;
    if (glfwGetTime() - cooldown > 1) {
        component_destroy_children(comp);
        if (comp->sub_id == WINDOW_FPS) {
            char text[50], num[20];
            strcpy(text, "FPS ");
            sprintf(num, "%.0f", window.fps);
            strncat(text, num, 20);
            component_add_text(comp, text, 30, 0.1, 0.1);
            printf("%s\n", text);
            cooldown = glfwGetTime();
        } else if (comp->sub_id == GAME_FPS) {
            char text[50], num[20];
            strcpy(text, "RENDER ");
            sprintf(num, "%.0f", window.fps);
            strncat(text, num, 20);
            printf("%s\n", text);
            cooldown = glfwGetTime();
        }
    }
}

void comp_textbox_hover_on(Component *comp)
{
    
}

void comp_textbox_hover_off(Component *comp)
{
    
}