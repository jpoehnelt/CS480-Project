/*
 Justin Poehnelt
 Ian Humphrey
 Tomas Zukowski
 
 CS 480
 Homework 7
 4/9/15
 */

#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <syslog.h>

#include "daemon.h"

#define PORT 8989
#define NUM_CONNECTIONS 10

void runserver();
void *handle_client(void *arg);
