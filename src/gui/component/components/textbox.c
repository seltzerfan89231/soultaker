#include "../component.h"
#include <string.h>
#include <stdio.h>

#define WINDOW_FPS 0
#define GAME_FPS 1

void comp_textbox_update(Component *comp)
{
    static f32 cooldown;
    if (glfwGetTime() - cooldown > 1) {
        component_destroy_children(comp);
        if (comp->sub_id == WINDOW_FPS) {
            char text[50], num[20];
            strcpy(text, "FPS ");
            sprintf(num, "%.0f", window.fps);
            strncat(text, num, 20);
            component_set_text(comp, 10, text);
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

void comp_textbox_mouse_button_callback(Component *comp, i32 button, i32 action)
{

}

void comp_textbox_key_callback(Component *comp, i32 key, i32 scancode, i32 action, i32 mods)
{

}

void comp_textbox_hover_callback(Component *comp, i32 action)
{

}
