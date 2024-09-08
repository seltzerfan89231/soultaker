#ifndef NETWORKING_H
#define NETWORKING_H

#include "../util/type.h"

int networking_init(void);
void networking_destroy(void);
int networking_host(void);
int networking_join(void);

void chat_host_init(void);
void chat_join_init(void);
void chat_send_message(char *message);
void networking_chat_destroy(void);

#endif