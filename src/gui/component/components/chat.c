#include "../component.h"
#include <stdlib.h>
#include <string.h>

static bool typing;

static void chat_input(Component *comp, i32 key)
{
    if (!typing)
        return;
    i32 len = (comp->text == NULL) ? 0 : strlen(comp->text);
    char* text = malloc((len + 2) * sizeof(char));
    strncpy(text, comp->text, len);
    strncat(text, &char_map[key].character, 1);
    component_set_text(comp, 7, text);
    free(text);
}

void comp_chat_create(Component *comp)
{
    comp->interactable = TRUE;
    comp->a = 0.0;
    Component *chat_log = component_create(0, 0.1, 1, 1, COMP_DEFAULT, COLOR_TEX);
    chat_log->r = chat_log->g = chat_log->b = chat_log->a = 0.3;
    chat_log->down_text = TRUE;
    component_set_text(chat_log, 7, "Hello World jajaja\nthe quick brown fox jumped over the lazy dog\npoo poo pooooooooooooooooooo");
    component_attach(comp, chat_log);
    Component *chat_input = component_create(0, 0, 1, 0.07, COMP_DEFAULT, COLOR_TEX);
    chat_input->r = chat_input->g = chat_input->b = chat_input->a = 0.45;
    component_attach(comp, chat_input);
}

void comp_chat_destroy(Component *comp)
{
    
}

void comp_chat_update(Component *comp)
{
    
}

void comp_chat_mouse_button_callback(Component *comp, i32 button, i32 action)
{

}

void comp_chat_key_callback(Component *comp, i32 key, i32 scancode, i32 action, i32 mods)
{
    if (key == GLFW_KEY_ENTER && action == GLFW_PRESS) {
        typing = 1 - typing;
        component_pause_input(comp, typing);
    }
    if (key >= 0 && key < 128 && action == GLFW_PRESS)
        chat_input(comp->children[1], key);
}

void comp_chat_hover_callback(Component *comp, i32 action)
{

}
