#ifndef CHAT_H 
#define CHAT_H 

#include "../util/type.h"
#include "../game/game.h"

typedef struct {
    i32 log_len;
    char* log;
} Chat;

void chat_init(void);
char* chat_get_log(void);
void chat_run_command(char* command);
void chat_writeline(char* text);
void chat_send_input(char* input);
void chat_destroy(void);

#endif