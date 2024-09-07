#include "../component.h"
#include <stdlib.h>
#include <string.h>

static bool typing;

static char num_to_sym[] = { ')', '!', '@', '#', '$', '%', '^', '&', '*', '(' };

#define _KEY_CASE_SHIFT(_c, _sc) \
    case _c : c = (shift) ? _sc : _c; break;

#define _KEY_CASE(_c) \
    case _c : c = _c; break;


static char get_char(i32 key, i32 mods)
{
    char c = '\0';
    bool shift, caps;
    shift = mods & GLFW_MOD_SHIFT;
    caps = mods & GLFW_MOD_CAPS_LOCK;
    if (key >= 'A' && key < 'Z')
        c = char_map[key + ((shift ^ caps) ? 0 : 'a' - 'A')].character;
    else if (key >= '0' && key < '9')
        c = (shift) ? num_to_sym[key - '0'] : char_map[key].character;
    switch (key) {
        _KEY_CASE(' ')
        _KEY_CASE('\t')
        _KEY_CASE_SHIFT('`', '~')
        _KEY_CASE_SHIFT('-', '_')
        _KEY_CASE_SHIFT('=', '+')
        _KEY_CASE_SHIFT('[', '{')
        _KEY_CASE_SHIFT(']', '}')
        _KEY_CASE_SHIFT('\\', '|')
        _KEY_CASE_SHIFT(';', ':')
        _KEY_CASE_SHIFT('\'', '\"')
        _KEY_CASE_SHIFT(',', '<')
        _KEY_CASE_SHIFT('.', '>')
        _KEY_CASE_SHIFT('/', '?')
    }
    return c;
}

static void chat_input(Component *comp, i32 key, i32 mods)
{
    if (!typing)
        return;
    i32 len = (comp->text == NULL) ? 0 : strlen(comp->text);
    if (len > 100)
        return;
    char c = get_char(key, mods);
    char* text = malloc((len + 2) * sizeof(char));
    strncpy(text, comp->text, len);
    text[len] = c;
    text[len+1] = '\0';
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
    if (key >= 0 && key < 128 && action != GLFW_RELEASE)
        chat_input(comp->children[1], key, mods);
}

void comp_chat_hover_callback(Component *comp, i32 action)
{

}
