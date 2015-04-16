#include "main.h"
int main() {
	dameon_init();
	
   	runserver();

	return 1;
}

void runserver() {

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