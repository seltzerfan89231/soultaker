#include "chat.h"
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdio.h>

Chat chat;

void chat_init(void)
{
    chat.log = malloc(sizeof(char));
    chat.log[0] = '\0';
    chat.log_len = 0;
}

char* chat_get_log(void)
{
    return chat.log;
}

void chat_writeline(char* text)
{
    assert(text != NULL);
    i32 len_log, len_text, new_len;
    len_text = strlen(text);
    len_log = chat.log_len;
    chat.log = realloc(chat.log, (len_text + len_log + 2) * sizeof(char));
    strncat(chat.log, text, len_text + 1);
    strncat(chat.log, "\n", 2);
    chat.log_len = len_text + len_log + 1;
}

void chat_send_input(char* input)
{
    if (input == NULL)
        return;
    if (input[0] == '/')
        chat_run_command(input);
    else {
        i32 len_name, len_input;
        char* name = "Fancy> ";
        len_name = strlen(name), len_input = strlen(input);
        char* text = malloc((len_name + len_input + 1) * sizeof(char));
        strncpy(text, name, len_name + 1);
        strncat(text, input, len_input + 1);
        chat_writeline(text);
    }
}

void chat_destroy(void)
{
    free(chat.log);
}

static char** split_string(char* str, char delim)
{
    i32 l, r, c, str_len;
    l = r = c = 0;
    str_len = strlen(str);
    for (l = r = c = 0; r < str_len; l = ++r) {
        while (r < str_len && str[r] != delim)
            r++;
        if (r > l)
            c++;
    }
    char** list = malloc((c + 1) * sizeof(char*));
    list[c] = NULL;
    for (l = r = c = 0; r < str_len; l = ++r) {
        while (r < str_len && str[r] != delim)
            r++;
        if (r > l) {
            list[c] = malloc((r - l + 1) * sizeof(char));
            strncpy(list[c], str + l, r - l);
            list[c][r - l] = '\0';
            c++;
        }
    }
    return list;
}

void chat_run_command(char* command)
{
    char** list = split_string(command, ' ');
    chat_writeline("Unrecognized command");
    for (i32 i = 0; list[i] != NULL; i++) {
        puts(list[i]);
        free(list[i]);
    }
    free(list);
}