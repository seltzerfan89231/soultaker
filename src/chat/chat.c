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

void chat_run_command(char* command)
{
    chat_writeline("Unrecognized command");
}