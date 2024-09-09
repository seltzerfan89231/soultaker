#include "../component.h"
#include "../../../chat/chat.h"
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

static void chat_input_append_char(Component* chat_input, i32 key, i32 mods)
{
    if (!typing)
        return;
    i32 len = (chat_input->text == NULL) ? 0 : strlen(chat_input->text);
    if (len > 100)
        return;
    char c = get_char(key, mods);
    char* text = malloc((len + 2) * sizeof(char));
    strncpy(text, chat_input->text, len);
    text[len] = c;
    text[len+1] = '\0';
    component_set_text(chat_input, 7, text);
    free(text);
}

static void chat_input_backspace_char(Component* chat_input, i32 key)
{
    if (chat_input->text == NULL)
        return;
    if (!typing)
        return;
    i32 len = strlen(chat_input->text);
    char* text = malloc(len * sizeof(char));
    strncpy(text, chat_input->text, len - 1);
    text[len-1] = '\0';
    component_set_text(chat_input, 7, text);
    free(text);
}

void comp_chat_create(Component *comp)
{
    comp->interactable = TRUE;
    comp->a = 0.0;
    Component *chat_log = component_create(0, 0.1, 1, 1, COMP_DEFAULT, COLOR_TEX);
    chat_log->r = chat_log->g = chat_log->b = chat_log->a = 0.3;
    chat_log->alignment.y = ALIGN_DOWN;
    component_set_text(chat_log, 7, "");
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
    Component* chat_log = comp->children[0];
    Component* chat_input = comp->children[1];
    if (key == GLFW_KEY_ENTER && action == GLFW_PRESS) {
        typing = 1 - typing;
        component_pause_input(comp, typing);
        if (!typing) {
            chat_send_input(chat_input->text);
            component_set_text(chat_input, 7, "");
            component_set_text(chat_log, 7, chat_get_log());
        }
    }
    if (key >= 0 && key < 128 && action != GLFW_RELEASE)
        chat_input_append_char(chat_input, key, mods);
    if (key == GLFW_KEY_BACKSPACE && action != GLFW_RELEASE)
        chat_input_backspace_char(chat_input, key);
}

void comp_chat_hover_callback(Component *comp, i32 action)
{

}
