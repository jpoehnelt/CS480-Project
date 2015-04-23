/*
Justin Poehnelt
Ian Humphrey
Tomas Zukowski
 
CS 480
Homework 9
4/26/15
*/



#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <syslog.h>

void dameon_init();
void dameon_exit();
