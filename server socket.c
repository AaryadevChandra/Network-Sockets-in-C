#include<stdio.h>
#include <WS2tcpip.h>
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include<Winsock2.h>

#pragma comment(lib, "Ws2_32.lib")

void displaybuffer(char* buffer)
{   
    while(*buffer != '\0')
    {
        printf("%c", *buffer);
        buffer += 1;
    }

    printf("\n");
}

int main()
{
    WSADATA wsadata;

    printf("\nInitializing Winsock...");

    if(WSAStartup(MAKEWORD(2,2), &wsadata) != 0)
    {
        printf("\n\nError initializing winsock:%d", WSAGetLastError());
        return -1;
    }

    printf("Winsock initialized");

    printf("\n\nCreating Server Socket...");

    SOCKET server_socket = INVALID_SOCKET;

    if((server_socket = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET)
    {
        printf("\n\nError creating server socket:%d", WSAGetLastError());
        return -1;
    }

    printf("\n\nServer socket created.");

    printf("\n\nAttempting to bind the server socket...");

    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(6969);
    server_addr.sin_addr.S_un.S_addr = INADDR_ANY;

    if(bind(server_socket, (struct sockaddr*)&server_addr, sizeof(server_addr))!=0)
    {
        printf("\n\nError binding server socket");
    }

    printf("Server socket binding successfull");

    SOCKET client_socket = INVALID_SOCKET;
    struct sockaddr_in client_addr;
    int client_addr_size = sizeof(client_addr);


    listen(server_socket, SOMAXCONN);

    printf("\n\nServer socket online, listening for connections...");

    client_socket = accept(server_socket, (struct sockaddr*)&client_addr, &client_addr_size);

    printf("\n\nConnected on port %d\n", ntohs(client_addr.sin_port));


    char recvBuffer[256];

    while(1)
    {
        recv(client_socket, recvBuffer, 256, 0);


        displaybuffer(recvBuffer);

        printf("\n");
    }

    getchar();
    
}