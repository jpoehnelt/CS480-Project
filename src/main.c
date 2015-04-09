


<<<<<<< Updated upstream

#include "main.h"
int main() {
	dameon_init();
	
	while(1) {
		syslog(LOG_NOTICE, "Running Server");
		sleep(5);
	}

	return 1;
=======
#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <syslog.h>


void dameon_run();
void runserver();

int main() {
    dameon_run();
    
    return EXIT_SUCCESS;
}

void dameon_run() {
    pid_t pid, sid;
    
    // Create child process
    if ((pid = fork()) < 0) {
        printf("Fork failure!\n");
        exit(1);
    }
    
    // Kill parent
    if (pid > 0) {
        exit(0);
    }
    
    if (pid == 0) {
        sid = setsid();
        if (sid < 0) {
            perror("setsid failed");
            exit(1);
        }
        printf("Daemon PID: %d\n", getpid());
    }
    
    if(chdir("/tmp") < 0){
        perror("Could not change directory.");
        exit(1);
    }
    
    // umask(0);
    
    // Close file descript
    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);
    
    setlogmask (LOG_UPTO (LOG_NOTICE));
    openlog ("Daemon Webserver", LOG_CONS | LOG_PID | LOG_NDELAY, LOG_LOCAL1);
    syslog (LOG_NOTICE, "Program started by User: %d, PID: %d", getuid(), getpid());
    
    
    // Catch Signals
    signal(SIGUSR1, dameon_signal);
    
    runserver();
    
    return;
>>>>>>> Stashed changes
}