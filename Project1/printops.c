#include <string.h>
#include <unistd.h>
#include <stdio.h> 
#include <stdlib.h>

#include "fileop.h"
/*
Name: Samuel Casey
BlazerId: scasey18
Project #: 1
*/
typedef void printFunc(char* loc, char* fn, int tab);

//Function to print the appropriate amount of tabs per line
void printTabs(int tabs){
	int i;
	for (i = 0; i< tabs; i++){
		printf("\t");
	}
}

//Direct the usage of printing the Directory
void DIRop(char* loc, char* fn, int tab){
	printf("%s\n", fn);
	strcat(loc, "/");
	printDIR(loc, tab+1, printResult);
}

//Prints out the Symbolic link that is avaliable
void LINKop(char* loc, char* fn, int tab){
	char buf1[1024];
	readlink(loc, buf1, sizeof(buf1));
	printf("%s (%s)\n", fn, buf1);
}

//Vague print function for all file types
void printFile(char* loc, char* fn, int tab, printFunc f){
	printTabs(tab+1); // all options requires printing tabs
	f(loc, fn, tab);
}

