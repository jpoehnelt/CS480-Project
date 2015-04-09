#include "main.h"
int main() {
	dameon_init();
	
    // Run the process code
    // Wait for 5 seconds and print to the system log
	while(1) {
		syslog(LOG_NOTICE, "Running Server");
		sleep(5);
	}

	return 1;
}