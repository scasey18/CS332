#ifndef _FILEOP_H_  
#include <unistd.h>
#include <stdio.h> 
#include <stdlib.h>
#include <dirent.h> 
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
/*
Name: Samuel Casey
BlazerId: scasey18
Project #: 1
*/
typedef void printF(char* Dirloc, char* fn, int tab);
void printResult(char* Dirloc, char* fn, int tab);
void printDIR(char* Dirloc,int tab, printF f);
#endif 