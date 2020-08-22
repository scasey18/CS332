#ifndef _COMMANDS_H_  
#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <unistd.h>
/*
Name: Samuel Casey
BlazerId: scasey18
Project #: 2
*/
void list (char** args, int count);
void help (char** args, int count);
void cd (char** args, int count);
void otherFuncs(char** args, int count);
void history (char** args, int count);
#endif 