/*
 Justin Poehnelt
 Ian Humphrey
 Tomas Zukowski
 
 CS 480
 Homework 8
 4/19/15
 */

#include "client.h"

int main() {
    
    // arrays to the client and server messages
    char message[100] , server_reply[100];
    
    // declare server socket and client address struct
    int client_socket;
    struct sockaddr_in client_address;
    
    // create the socket -- TCP socket
    client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket == -1)
    {
        syslog (LOG_NOTICE,"Failed to create client socket");
        exit(1);
    }
    
    client_address.sin_family = AF_INET;
    client_address.sin_addr.s_addr = inet_addr(SERVER_ADDR);
    client_address.sin_port = htons(PORT);
    
    if(connect(client_socket, (struct sockaddr *) &client_address, sizeof(client_address)) == -1)
    {
        printf("Failed to establish connection between the client and server");
    }
    
    while(1) {
        scanf("%s", message);
        write(client_socket, message, sizeof(message));
        read(client_socket, server_reply, sizeof(server_reply));
        puts(server_reply);
        if (strstr(message, "q"))
            break;
    }     
    
    close(client_socket);
    return 0;
}


