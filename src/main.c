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
        exit(1);
    }

    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = inet_addr("127.0.0.1");
    server_address.sin_port = htons(PORT);
    
	// Bind Port to Socket
    if (bind(server_socket, (struct sockaddr*)&server_address, sizeof(server_address)) == -1) 
    {
        printf("Failed to bind server socket");
        exit(1);
    }

	// Listen for Connections with Queue 
    listen(server_socket, NUM_CONNECTIONS);

	while (1) {
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
    int client_socket = (int) arg;
    int done = 0;
    char input;

    while (!done) {
        read(client_socket, &input, 1);
        
        if (input == 'q')
        {
            write(client_socket, &input, sizeof(char));
            break;
        }
        
        write(client_socket, &input, sizeof(char));
    }
    // close
    exit(0);
}
