/*
 Justin Poehnelt
 Ian Humphrey
 Tomas Zukowski
 
 CS 480
 Homework 8
 4/19/15
 */

#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <syslog.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>

#include "daemon.h"

#define PORT 8989
#define NUM_CONNECTIONS 10

void runserver();
void *handle_client(void *arg);
