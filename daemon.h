#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <syslog.h>

void dameon_run();
void dameon_signal(int sig_no);
void dameon_exit();
void runserver();