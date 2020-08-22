#ifndef _PRINTOPS_H_  
#include <string.h>
#include <unistd.h>
#include <stdio.h> 
#include <stdlib.h>
/*
Name: Samuel Casey
BlazerId: scasey18
Project #: 1
*/
typedef void printFunc(char* loc, char* fn, int tab);
void DIRop(char* loc, char* fn, int tab);
void LINKop(char* loc, char* fn, int tab);
void printTabs(int tabs);
void printFile(char* loc, char* fn, int tab, printFunc f);
#endif 