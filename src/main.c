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
    // initialize current process as daemon proces
	dameon_init();
	// create the server
   	runserver();

    // this line should never execute
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

    // set necessary connection information
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

    // run and wait for connections
	while (1) {
        int client_socket = accept(server_socket, NULL, NULL);
        // DEBUG syslog(LOG_NOTICE, "SOCKET FD -> %d", client_socket);
        
        // create a thread for each client connection
        pthread_t thread;
        if(pthread_create(&thread, NULL, handle_client, (void*)&client_socket) != 0)
        {
            // log error if there was an issue creating new thread
            syslog(LOG_NOTICE, "Error creating thread for client");
        }			

        // detach the created thread from the server so resources auto handled on termination
        pthread_detach(thread);
	}
}


void* handle_client(void* arg) {
    // recast the client socket fd as an int
    // i.e. dereference the casted int pointer
    int client_socket = *(int*) arg;

    // DEBUG syslog(LOG_NOTICE, "handle_client fd -- %d", client_socket);
    char input[100];
    syslog (LOG_NOTICE, "Thread created for socket at %d.", client_socket);

    // keep communicating until 'q' encountered 
    while (1) {
        // read into input buffer the data from client_socket
        read(client_socket, input, sizeof(input));

        int i;
        
        if (sscanf(input, "%d", &i) == 0) 
        {
            syslog(LOG_NOTICE, "Could not convert %s to integer.", input);
        }

        syslog(LOG_NOTICE, "Integer: %d", i);

        // still need to write back to client_socket when quitting
        if (strstr(input,"q"))
        {
            write(client_socket, input, sizeof(input));
            break;
        }
        
        // write the read data into client_socket
        write(client_socket, input, sizeof(input));
    }
    
    // close socket
    syslog (LOG_NOTICE, "Closing connection");
    close(client_socket);

    // terminate the client's thread
    pthread_exit(0);
}
