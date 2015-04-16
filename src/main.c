/*
 Justin Poehnelt
 Ian Humphrey
 Tomas Zukowski
 
 CS 480
 Homework 8
 4/19/15
 */

#include "main.h"
int main() {
	dameon_init();
	
   	runserver();

	return 1;
}

void runserver() {
    // declare server socket and server address struct
    int server_socket;
    struct sockaddr_in server_address;

    // create the socket -- TCP socket
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == -1) 
    {
        printf("Failed to create server socket");
    }

    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = inet_addr("127.0.0.1");
    server_address.sin_port = htons(PORT);
    
    
	// Make Socket

	// Bind Port to Socket

	// Listen for Connections with Queue 

	WHILE (1) {
        int client_socket = accept(server_socket, NULL, NULL);
        
        pthread_t thread;
        if(pthread_create(&thread, NULL, handle_client, (void*)&client_socket) != 0)
        {
            // log error if there was an issue creating new thread
        }
		// Accept Connection

		// Do threading		
	}
}

void* handle_client(void* arg) {
    int client_socket = *((int)arg);
    
    while (!done) {
        read(
        
        if (input == 'q')
        {
            write(client_socket, &input, sizeof(char));
            break;
        }
        
        write(client_socket, &input, sizeof(char));
    }
    // close
}
