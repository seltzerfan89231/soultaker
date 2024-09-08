#include "chat.h"
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdio.h>
#include <ctype.h>

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
    if (text == NULL)
        return;
    i32 len_log, len_text, new_len;
    len_text = strlen(text);
    len_log = chat.log_len;
    chat.log = realloc(chat.log, (len_text + len_log + 2) * sizeof(char));
    memcpy(chat.log + len_log, text, len_text + 1);
    memcpy(chat.log + len_log + len_text, "\n", 2);
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
        memcpy(text, name, len_name + 1);
        memcpy(text + len_name, input, len_input + 1);
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

static bool isnumber(char* str) 
{
    for (i32 i = 0; str[i] != '\0'; i++)
        if (!isdigit(str[i]))
            return FALSE;
    return TRUE;
}

#define MAX_ARG_LEN 20
#define MAX_OUTPUT_LEN 100
#define INITIAL 0
#define UNREGONIZED 1
#define GAME 2
#define GAME_SETUP 3
#define GAME_SETUP_SUCCESS 4
#define GAME_SETUP_ERROR 5
#define GAME_PAUSE 6

static struct {
    i32 int1;
} command_args;

static char* execute_command(i32 state)
{
    static char output_message[MAX_OUTPUT_LEN + 1];
    switch (state) {
        case UNREGONIZED:
            return "Unrecognized Command";
        case GAME:
            return "/game {setup, pause}";
        case GAME_SETUP:
            return "/game setup {1-4}";
        case GAME_SETUP_SUCCESS:
            sprintf(output_message, "Successfully loaded level %d", command_args.int1);
            game_setup(command_args.int1);
            return output_message;
        case GAME_SETUP_ERROR:
            return "/game setup {1-4}";
        case GAME_PAUSE:
            game_pause();
            return NULL;
    }
    return NULL;
}

static char* parse_command(char** args, i32 idx, i32 state)
{
    char* arg = args[idx];
    if (arg == NULL)
        return execute_command(state);
    i32 new_state = UNREGONIZED;
    switch (state) {
        case INITIAL:
            if (strncmp(arg, "/game", MAX_ARG_LEN) == 0)
                new_state = GAME;
            break;
        case GAME:
            if (strncmp(arg, "setup", MAX_ARG_LEN) == 0)
                new_state = GAME_SETUP;
            else if (strncmp(arg, "pause", MAX_ARG_LEN) == 0)
                new_state = GAME_PAUSE;
            break;  
        case GAME_SETUP:
            if (!isnumber(arg))
                new_state = GAME_SETUP_ERROR;
            i32 num = atoi(arg);
            if (num >= 1 && num <= 4) {
                new_state = GAME_SETUP_SUCCESS;
                command_args.int1 = num;
            }
            else
                new_state = GAME_SETUP_ERROR;
            break;
    }
    return parse_command(args, idx + 1, new_state);
}

void chat_run_command(char* command)
{
    char** args = split_string(command, ' ');
    chat_writeline(parse_command(args, 0, INITIAL));
    for (i32 i = 0; args[i] != NULL; i++)
        free(args[i]);
    free(args);
}