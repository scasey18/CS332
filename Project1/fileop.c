#include <unistd.h>
#include <stdio.h> 
#include <stdlib.h>
#include <dirent.h> 
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>

#include "printops.h"
/*
Name: Samuel Casey
BlazerId: scasey18
Project #: 1
*/
extern char* searchString;
extern int minsize;

typedef void printF(char* Dirloc, char* fn, int tab);

void printResult(char* Dirloc, char* fn, int tab);
void printDIR(char* Dirloc,int tab, printF f);

void printResult(char* Dirloc, char* fn, int tab){
	struct stat buf;
	//fix the loc for lstat and retrieve lstat info
	char loc[strlen(Dirloc)+strlen(fn)+1];
	strcpy(loc,Dirloc);
	strcat(loc,fn);
	lstat(loc, &buf);
	//dont print if string does not contain provided string
	if (strstr(fn, searchString) != NULL){
		
		if (S_ISDIR(buf.st_mode)){
			printFile(loc, fn, tab, DIRop);
		}
		else if (S_ISLNK(buf.st_mode)){
			printFile(loc, fn, tab, LINKop);
		}
		else if (buf.st_size >= minsize){
			printTabs(tab+1);
			printf("%s\n", fn);
		}
	}
}

/* This method is used to iterate through the provided Directory (Dirloc)
*  Tab is used for the output to the console
*/
void printDIR(char* Dirloc,int tab, printF f){
	struct dirent *dirent; 
	DIR *parentDir = opendir (Dirloc);
	if (parentDir == NULL) { 
		printf ("Error opening directory '%s'\n", Dirloc); 
		exit (-1);
	} 
	while((dirent = readdir(parentDir)) != NULL){
		//This is too make sure there is no loops as all folders have this 
		if (strcmp((*dirent).d_name,".") && strcmp((*dirent).d_name,"..")){
			f(Dirloc, (*dirent).d_name,tab);
		}
	} 
	closedir (parentDir);
}

