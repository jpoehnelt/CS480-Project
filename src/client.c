#include "client.h"

int main() {
	
    client_socket = socket(AF_INET, SOCK_STREAM, 0);
    
    client_address.sin_family = AF_INET;
    client_address.sin_addr.s_addr = inet_addr(SERVER_ADDR);
    client_address.sin_port = htons(PORT);
    
    if(connect(client_socket, (struct sockaddr *) &client_address, sizeof(client_address)) == -1)
    {
        // log error if there are issues creating a connection
    }
    
    // client loop
    
	return 0;
}