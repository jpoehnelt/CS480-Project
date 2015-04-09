
#include "main.h"
int main() {
	dameon_init();
	
	while(1) {
		syslog(LOG_NOTICE, "Running Server");
		sleep(5);
	}

	return 1;
}