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
        syslog (LOG_NOTICE,"Failed to create server socket");
        exit(1);
    }

    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = inet_addr("127.0.0.1");
    server_address.sin_port = htons(PORT);
    
	// Bind Port to Socket
    if (bind(server_socket, (struct sockaddr*)&server_address, sizeof(server_address)) == -1) 
    {
        syslog (LOG_NOTICE, "Failed to bind server socket");
        exit(1);
    }

	// Listen for Connections with Queue 
    listen(server_socket, NUM_CONNECTIONS);

    syslog (LOG_NOTICE, "Waiting for connections on port: %d", PORT);

	while (1) {
        int client_socket = accept(server_socket, NULL, NULL);
        // DEBUG syslog(LOG_NOTICE, "SOCKET FD -> %d", client_socket);
        
        pthread_t thread;
        if(pthread_create(&thread, NULL, handle_client, (void*)&client_socket) != 0)
        {
            // log error if there was an issue creating new thread
        }			

        pthread_detach(thread);
	}
}

void* handle_client(void* arg) {
    int client_socket = *(int*) arg;

    // DEBUG syslog(LOG_NOTICE, "handle_client fd -- %d", client_socket);
    char input[100];
    syslog (LOG_NOTICE, "Thread created for socket.");

    while (1) {
        read(client_socket, input, sizeof(input));


        if (*input == 'q')
        {
            write(client_socket, input, sizeof(input));
            break;
        }
        write(client_socket, input, sizeof(input));
    }
    
    // close socket
    syslog (LOG_NOTICE, "Closing connection");
    close(client_socket);

    pthread_exit(0);
}
