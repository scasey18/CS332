#ifndef _PARSELINE_H_  
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
/*
Name: Samuel Casey
BlazerId: scasey18
Project #: 2
*/
void detectInput(char** args, int count, char* name);
void parseLine(char* line);
char** argParser(char* line);
int firstWord(char* line);
int getArgSize(char** args);
void freeArray(char** args, int count);
#endif 