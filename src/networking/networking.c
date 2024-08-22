#include "networking.h"
#include "chat.h"
#include <stdio.h>

Networking net;

int networking_init(void)
{
    printf("Initializing Winsock...\n");
    if (WSAStartup(MAKEWORD(2,2), &net.wsa) != 0) {
        printf("Failed. Error Code: %d", WSAGetLastError());
        return 1;
    }
    net.initialized = TRUE;

}

void networking_destroy(void)
{
    chat_destroy();
    if (net.initialized) {
        closesocket(net.socket);
        WSACleanup();
        puts("Succesfully cleaned up.");
    } else {
        puts("WSA was not initialized.");
    }
    net.initialized = FALSE;
}

int networking_host(void)
{
    puts("Creating host...");
    net.socket = socket(AF_INET, SOCK_DGRAM, 0);
    if (net.socket == INVALID_SOCKET) {
        printf("Could not create socket : %d", WSAGetLastError());
        networking_destroy();
        return 1;
    }

    net.address.sin_family = AF_INET;
    net.address.sin_addr.s_addr = INADDR_ANY;
    net.address.sin_port = htons(SERVER_PORT);
    
    if (bind(net.socket, (struct sockaddr *)&net.address, sizeof(net.address)) == SOCKET_ERROR) {
        printf("Bind failed with error code : %d", WSAGetLastError());
        closesocket(net.socket);
        WSACleanup();
        return 1;
    }

    printf("Host initialized on port %d, starting chat server...\n", SERVER_PORT);
    chat_host_init();
}

int networking_join(void)
{
    printf("Joining...");
    net.socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (net.socket == INVALID_SOCKET) {
        printf("Could not create socket : %d", WSAGetLastError());
        networking_destroy();
        return 1;
    }
    chat_join_init();
}