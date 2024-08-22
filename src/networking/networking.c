#include "networking.h"
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <winsock2.h>
// use atomic bool

#define BUFFER_SIZE 2000
#define MAX_CLIENTS 4

#define SERVER_ADDR "127.0.0.1"
#define CLIENT_ADDR "127.0.0.1"
#define SERVER_PORT 12345

typedef struct {
    WSADATA wsa;
    bool initialized;
    struct sockaddr_in address;
    SOCKET socket;
} Networking;

static Networking net;

static pthread_t host_thread_id;
static pthread_t client_thread_id;
static volatile bool kill_thread;
static bool chat_initialized;

static void *host_listener(void *vargp);
static void *client_listener(void *vargp);

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
    puts("Joining...");
    net.socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (net.socket == INVALID_SOCKET) {
        printf("Could not create socket : %d", WSAGetLastError());
        networking_destroy();
        return 1;
    }
    chat_join_init();
}

void chat_host_init(void)
{
    kill_thread = FALSE;
    pthread_create(&host_thread_id, NULL, host_listener, NULL);
    chat_initialized = TRUE;
    puts("Chat host initalized");
}

void chat_join_init(void)
{
    kill_thread = FALSE;
    pthread_create(&client_thread_id, NULL, client_listener, NULL);
    chat_initialized = TRUE;
    puts("Chat client initalized");
}

void chat_destroy(void)
{
    if (chat_initialized) {
        kill_thread = TRUE;
        pthread_join(host_thread_id, NULL);
        pthread_join(client_thread_id, NULL);
        puts("Successfully stopped chat.");
    } else {
        puts("Chat never initalized.");
    }
}

void chat_send_message(char *message)
{
    if(!chat_initialized)
        return;
}

static void *host_listener(void *vargp)
{
    struct sockaddr_in client_addr;
    int recv_len, client_addr_len;
    struct timeval timeout;
    FD_SET readfds;
    while (!kill_thread) {
        size_t message_size;
        char buffer[BUFFER_SIZE];
        client_addr_len = sizeof(client_addr);
        timeout.tv_sec = 1;
        timeout.tv_usec = 0;
        FD_ZERO(&readfds);
        FD_SET(net.socket, &readfds);
        int result = select(net.socket + 1, &readfds, NULL, NULL, &timeout);
        if (result == -1) {
            puts("Select error in host listener");
            pthread_exit(NULL);
        } else if (result == 0) {
            continue;
        }
        recv_len = recvfrom(net.socket, buffer, BUFFER_SIZE, 0, (struct sockaddr *)&client_addr, &client_addr_len);
        if (recv_len == SOCKET_ERROR) {
            printf("Host recv failed with error code : %d", WSAGetLastError());
            pthread_exit(NULL);
        }
        buffer[recv_len] = '\0';
        puts(buffer);
    }
}

static void *client_listener(void *vargp)
{
   /*  struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    if (!(server_addr.sin_addr.s_addr = inet_addr(SERVER_ADDR))) {
        printf("Invalid IP address");
        pthread_exit(NULL);
    }
    if (!(server_addr.sin_port = htons(SERVER_PORT))) {
        printf("Invalid port number");
        pthread_exit(NULL);
    };
    char *text = "Hello World.";
    if (sendto(net.socket, text, strlen(text), 0, (struct sockaddr *)&server_addr, sizeof(server_addr)) == SOCKET_ERROR) {
        puts("Failed to send message from client");
        pthread_exit(NULL);
    } */

    struct sockaddr_in server_addr;
    int recv_len, server_addr_len;
    struct timeval timeout;
    FD_SET readfds;
    int result = select(net.socket + 1, &readfds, NULL, NULL, &timeout);
    while (!kill_thread) {
        size_t message_size;
        char buffer[BUFFER_SIZE];
        timeout.tv_sec = 1;
        timeout.tv_usec = 0;
        FD_ZERO(&readfds);
        FD_SET(net.socket, &readfds);
        int result = select(net.socket + 1, &readfds, NULL, NULL, &timeout);
        if (result == -1) {
            puts("Select error in host listener");
            pthread_exit(NULL);
        } else if (result == 0) {
            puts("Timeout");
            continue;
        }

        recv_len = recvfrom(net.socket, buffer, BUFFER_SIZE, 0, (struct sockaddr *)&server_addr, &server_addr_len);
        if (recv_len == SOCKET_ERROR) {
            printf("Client recv failed : %d\n", WSAGetLastError());
            pthread_exit(NULL);
        }
        
        buffer[recv_len] = '\0';
        puts(buffer);
    }
}