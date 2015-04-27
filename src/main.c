/*
 Justin Poehnelt
 Ian Humphrey
 Tomas Zukowski
 
 CS 480
 Homework 9
 4/26/15
 */

#include "main.h"

int computed[MEMOIZE_LIMIT] = {0};
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

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
        // -1 indicates invalid input
        int result = -1;

        // read into input buffer the data from client_socket
        read(client_socket, input, sizeof(input));

        long l = 0;
        
        if (sscanf(input, "%lu", &l) == 0) 
        {
            syslog(LOG_NOTICE, "Could not convert %s to long.", input);
        }

        syslog(LOG_NOTICE, "Long: %lu", l);

        // 0 is 0 steps, don't memoize pass 1000 (array out of bounds)
        if (l > 0) {
            result = three_a_one(l);
        }

        syslog(LOG_NOTICE, "Result for 3A + 1 on %lu: %d", l, result);

        // still need to write back to client_socket when quitting
        if (strstr(input,"q"))
        {
            write(client_socket, input, sizeof(input));
            break;
        }
        
        // write the read data into client_socket
        write(client_socket, &result, sizeof(int));
    }
    
    // close socket
    syslog (LOG_NOTICE, "Closing connection");
    close(client_socket);

    // terminate the client's thread
    pthread_exit(0);
}


int three_a_one(long input) {
    int total_steps = 0, memoized = 0;
    long next = input;

    syslog (LOG_NOTICE, "Calculating 3A + 1 for %lu", input);
     // base case
    if (input <= 1) {
        return 0;
    }

    // memoized case
    if ((int)input <= MEMOIZE_LIMIT && (memoized = computed[input]) != 0) {
        syslog (LOG_NOTICE, "Found 3A + 1 for %lu in memoization table", input);
        return memoized;
    }

    // even case
    if (input % 2 == 0) {
        next /= 2;
    }
    // odd case
    else {
        next = 3 * input + 1;
    }

    total_steps = three_a_one(next) + 1;

    // save to memoization table
    if ((int)input <= MEMOIZE_LIMIT) {
        pthread_mutex_lock(&mutex);
        computed[input] = total_steps;
        syslog (LOG_NOTICE, "Set memoization table for %lu to %d", input, computed[input]); 
        pthread_mutex_unlock(&mutex);
    }

    return total_steps;
}



