#include "chat.h"
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <winsock2.h>
// use atomic bool

#define BUFFER_SIZE 2000
#define MAX_CLIENTS 4

static pthread_t host_thread_id;
static pthread_t client_thread_id;
static volatile bool kill_thread;
static bool initialized;

Chat chat;

static void *host_listener(void *vargp);
static void *client_listener(void *vargp);

void chat_host_init(void)
{
    kill_thread = FALSE;
    pthread_create(&host_thread_id, NULL, host_listener, NULL);
    initialized = TRUE;
    puts("Chat host initalized");
}

void chat_join_init(void)
{
    kill_thread = FALSE;
    pthread_create(&client_thread_id, NULL, client_listener, NULL);
    initialized = TRUE;
    puts("Chat client initalized");
}

void chat_destroy(void)
{
    if (initialized) {
        kill_thread = TRUE;
        pthread_join(host_thread_id, NULL);
        pthread_join(client_thread_id, NULL);
        puts("Successfully stopped chat.");
    } else {
        puts("Chat never initalized.");
    }
}

static void *host_listener(void *vargp)
{
    struct sockaddr_in client_addr;
    int recv_len, client_addr_len;
    struct timeval timeout;
    FD_SET readfds;
    while (!kill_thread) {
        int idx;
        size_t message_size;
        char buffer[BUFFER_SIZE];
        client_addr_len = sizeof(client_addr);
        timeout.tv_sec = 1;
        timeout.tv_usec = 0;
        FD_ZERO(&readfds);
        FD_SET(net.socket, &readfds);
        int result = select(net.socket + 1, &readfds, NULL, NULL, &timeout);
        if (result == -1) {
            puts("Select error");
            pthread_exit(NULL);
        } else if (result == 0) {
            continue;
        }
        recv_len = recvfrom(net.socket, buffer, BUFFER_SIZE, 0, (struct sockaddr *)&client_addr, &client_addr_len);
        if (recv_len == SOCKET_ERROR) {
            printf("Recv failed with error code : %d", WSAGetLastError());
            pthread_exit(NULL);
        }
        buffer[recv_len] = '\0';
        puts(buffer);
    }
}

static void *client_listener(void *vargp)
{
    struct sockaddr_in server_addr;
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
    }
}