#ifndef CHAT_H
#define CHAT_H

#include "../util/type.h"
#include "networking.h"

typedef struct {
    int x;
} Chat;

extern Chat chat;

void chat_host_init(void);
void chat_join_init(void);
void chat_destroy(void);

#endif