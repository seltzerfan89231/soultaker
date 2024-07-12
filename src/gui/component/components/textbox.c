#include "../component.h"
#include <string.h>
#include <stdio.h>

void comp_textbox_update(Component *comp)
{
    static f32 cooldown;
    if (glfwGetTime() - cooldown > 1) {
        char text[50], num[20];
        strcpy(text, "WINDOW ");
        sprintf(num, "%.0f", window.fps);
        strncat(text, num, 20);
        i32 len = strlen(text);
        for (i32 i = 0; i < len; i++) {
            comp->children[i]->tex = char_map[text[i]];
        }
        for (i32 i = len; i < comp->num_children; i++)
            comp->children[i]->tex = NO_TEX;
        cooldown = glfwGetTime();
    }
}

void comp_textbox_hover_on(Component *comp)
{
    
}

void comp_textbox_hover_off(Component *comp)
{
    
}