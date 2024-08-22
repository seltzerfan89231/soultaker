#ifndef NETWORKING_H
#define NETWORKING_H

#include "../util/type.h"
#include <winsock2.h>

#define SERVER_ADDR "127.0.0.1"
#define CLIENT_ADDR "127.0.0.1"
#define SERVER_PORT 12345

typedef struct {
    WSADATA wsa;
    bool initialized;
    struct sockaddr_in address;
    SOCKET socket;
} Networking;

extern Networking net;

int networking_init(void);
void networking_destroy(void);
int networking_host(void);
int networking_join(void);

#endif