#include "networking.h"
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <winsock2.h>
#include <string.h>
// use atomic bool

#define BUFFER_SIZE 2000
#define MAX_CLIENTS 4

#define SERVER_ADDR "127.0.0.1"
#define CLIENT_ADDR "127.0.0.1"
#define SERVER_PORT 5000
#define CLIENT_PORT 6000

static WSADATA wsa;
static bool wsa_initialized;

typedef struct {
    struct sockaddr_in address;
    SOCKET socket;
} Server;

typedef struct {
    struct sockaddr_in address;
    SOCKET socket;
} Client;

static Server server;
static Client client;

static pthread_t host_thread_id;
static pthread_t client_thread_id;
static volatile bool kill_thread;
static bool chat_initialized;

static void *host_listener(void *vargp);
static void *client_listener(void *vargp);

int networking_init(void)
{
    printf("Initializing Winsock...\n");
    if (WSAStartup(MAKEWORD(2,2), &wsa) != 0) {
        printf("Failed. Error Code: %d", WSAGetLastError());
        return 1;
    }
    wsa_initialized = TRUE;
}

void networking_destroy(void)
{
    networking_chat_destroy();
    if (wsa_initialized) {
        WSACleanup();
        //puts("Succesfully cleaned up.");
    } else {
        //puts("WSA was not initialized.");
    }
    wsa_initialized = FALSE;
}

static int create_server(void)
{
    puts("Creating host...");
    server.socket = socket(AF_INET, SOCK_DGRAM, 0);
    if (server.socket == INVALID_SOCKET) {
        printf("Could not create socket : %d", WSAGetLastError());
        networking_destroy();
        return 1;
    }

    server.address.sin_family = AF_INET;
    server.address.sin_addr.s_addr = INADDR_ANY;
    server.address.sin_port = htons(SERVER_PORT);
    
    if (bind(server.socket, (struct sockaddr *)&server.address, sizeof(server.address)) == SOCKET_ERROR) {
        printf("Bind failed with error code : %d", WSAGetLastError());
        closesocket(server.socket);
        WSACleanup();
        return 1;
    }

    printf("Host initialized on port %d, starting chat server...\n", SERVER_PORT);
    chat_host_init();
}

static int create_client(void)
{
    puts("Joining...");
    client.socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (client.socket == INVALID_SOCKET) {
        printf("Could not create socket : %d", WSAGetLastError());
        networking_destroy();
        return 1;
    }

    chat_join_init();
}

int networking_host(void)
{
    create_server();
    create_client();
}

int networking_join(void)
{
    create_client();
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

void networking_chat_destroy(void)
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
    if (sendto(client.socket, message, strlen(message), 0, (struct sockaddr *)&server_addr, sizeof(server_addr)) == SOCKET_ERROR) {
        puts("Failed to send message from client");
        pthread_exit(NULL);
    }
}

static int seen(struct sockaddr_in *clients, struct sockaddr_in client) {
    for (int i = 0; i < MAX_CLIENTS; i++)
        if (clients[i].sin_addr.s_addr == client.sin_addr.s_addr && clients[i].sin_port == client.sin_port)
            return i;
    return -1;
}

static void *host_listener(void *vargp)
{
    struct sockaddr_in client_addr, connected_clients[MAX_CLIENTS];
    int recv_len, client_addr_len, num_clients = 0, lens[MAX_CLIENTS];
    struct timeval timeout;
    FD_SET readfds;

    while (!kill_thread) {
        int idx;
        size_t message_size;
        char buffer[BUFFER_SIZE], message[BUFFER_SIZE], name[BUFFER_SIZE];
        client_addr_len = sizeof(client_addr);
        timeout.tv_sec = 1;
        timeout.tv_usec = 0;
        FD_ZERO(&readfds);
        FD_SET(server.socket, &readfds);
        int result = select(server.socket + 1, &readfds, NULL, NULL, &timeout);
        if (result == -1) {
            puts("Select error in host listener");
            pthread_exit(NULL);
        } else if (result == 0) {
            continue;
        }
        recv_len = recvfrom(server.socket, buffer, BUFFER_SIZE, 0, (struct sockaddr *)&client_addr, &client_addr_len);
        if (recv_len == SOCKET_ERROR) {
            printf("Host recv failed with error code : %d", WSAGetLastError());
            pthread_exit(NULL);
        }
        buffer[recv_len] = '\0';

        if ((idx = seen(connected_clients, client_addr)) == -1) {
            connected_clients[num_clients] = client_addr;
            lens[num_clients] = client_addr_len;
            idx = num_clients;
            num_clients++;
            printf("Successfully added %s.\n", buffer);
        }

        printf("Received message from client %d %s:%d: %s\n", idx + 1, inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port), buffer);
        sprintf(name, "Client %d", idx+1);
        strcat(strcat(strcpy(message, name), "> "), buffer);
        for (int i = 0; i < num_clients; i++) {
            if (sendto(server.socket, message, sizeof(message), 0, (struct sockaddr *)&connected_clients[i], lens[i]) == SOCKET_ERROR) {
                printf("Sendto failed with error code : %d", WSAGetLastError());
                pthread_exit(NULL);
            }
        }
    }
}

static void *client_listener(void *vargp)
{
    struct sockaddr_in server_addr;
    int recv_len, server_addr_len;
    struct timeval timeout;
    FD_SET readfds;

    server_addr.sin_family = AF_INET;
    if (!(server_addr.sin_addr.s_addr = inet_addr(SERVER_ADDR))) {
        printf("Invalid IP address");
        pthread_exit(NULL);
    }
    if (!(server_addr.sin_port = htons(SERVER_PORT))) {
        printf("Invalid port number");
        pthread_exit(NULL);
    };

    chat_send_message("Client 1");

    while (!kill_thread) {
        size_t message_size;
        char buffer[BUFFER_SIZE];
        timeout.tv_sec = 1;
        timeout.tv_usec = 0;
        FD_ZERO(&readfds);
        FD_SET(client.socket, &readfds);
        int result = select(client.socket + 1, &readfds, NULL, NULL, &timeout);
        if (result == -1) {
            puts("Select error in host listener");
            pthread_exit(NULL);
        } else if (result == 0) {
            continue;
        }
        recv_len = recvfrom(client.socket, buffer, BUFFER_SIZE, 0, NULL, NULL);
        if (recv_len == SOCKET_ERROR) {
            printf("Client recv failed : %d\n", WSAGetLastError());
            pthread_exit(NULL);
        }
        buffer[recv_len] = '\0';
        puts(buffer);
    }
}