/* ---------------
 Justin Poehnelt
 Ian Humphrey
 Tomas Zukowski
 
 CS 480
 Homework 7
 4/9/15
 --------------- */

#include "daemon.h"

void dameon_init() {
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

    // If setting the signal ID failed, print an error
	if (pid == 0) {
		sid = setsid();
		if (sid < 0) {
			perror("setsid failed");
			exit(1);
		}
        
        // Otherwise print the number of the process
		printf("Daemon PID: %d\n", getpid());
	}

    // Move the process into a common working directory
	if(chdir("/tmp") < 0){
		perror("Could not change directory.");
		exit(1);
	}

    // Grant all rights to allow the Daemon read and write access
    umask(0);

	// Close file descript
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	close(STDERR_FILENO);

    // Write the start of the process to the system log
	setlogmask (LOG_UPTO (LOG_NOTICE));
	openlog ("Daemon Webserver", LOG_CONS | LOG_PID | LOG_NDELAY, LOG_LOCAL1);
	syslog (LOG_NOTICE, "Program started by User: %d, PID: %d", getuid(), getpid());


	// Catch Signals
	signal(SIGUSR1, dameon_exit);

	return;
}

// Gracefully terminate the daemon process when the signal is caught
void dameon_exit(int sig_no) {
	syslog (LOG_NOTICE, "Caught Signal: %d", sig_no);
	syslog(LOG_NOTICE, "Program exiting");
	closelog ();
	exit(0);

}

