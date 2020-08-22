#ifndef _COMMANDS_H_  
#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
/*
Name: Samuel Casey
BlazerId: scasey18
Project #: 4
*/
void showJobs(char** args, int count);
void submitJob(char** args, int count, char* name);
void help(char** args, int count);
void otherFuncs(char** args, int count);
#endif 