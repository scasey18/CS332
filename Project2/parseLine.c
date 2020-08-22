#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "createProcess.h"
#include "commands.h"
/*
Name: Samuel Casey
BlazerId: scasey18
Project #: 2
*/

void printArray(char** args, int count){
	int i;
	for (i = 0; i < count; i++){
		printf("[%d] %s\n",i, args[i]);
	}
}
void freeArray(char** args, int count){
	int i;
	for (i = 0; i < count; i++){
		free(args[i]);
	}
	free(args);
}
/**
**  Determine commands built for the shell and those in path or source location
**/
void detectInput(char** args, int count){
	if (!strcmp("list", args[0])){
		createProcess(args, count, list);
	}
	else if (!strcmp("quit",args[0]) && count == 1){
		exit(0);
	}
	else if (!strcmp("cd", args[0])){
		//createProcess(args, count, cd);
		//can not change parent process enviornment from a child process
		//so this is the only function that cannot take place in the child process
		cd(args,count);
	}
	else if (!strcmp("help", args[0])){
		createProcess(args, count, help);
	}
	else if (!strcmp("history", args[0])){
		createProcess(args, count, history);
	}
	else {
		//if the rest of the processes fail then assume it is for another exec
		createProcess(args, count, otherFuncs);
	}
}
/**
** Parses the line taken in from the shell to determine the args
**/
void parseLine(char* line){
	char** args = malloc(1048 * sizeof(char *)); 
	int count = 0;
	int i; int len = strlen(line); int hold = 1;
	args[count] = malloc(1048 * sizeof(char));
	strcpy(args[count], "\0");
	for (i = 0; i < len; i++){
		if (line[i] == ' ' && hold == 1){
			count++;
			args[count] = malloc(1048 * sizeof(char));
			strcpy(args[count], "\0");
		}
		else if (line[i] == '"' && (hold == 1 || hold == 2)){
			switch(hold){
			case 1: hold = 2; break;
			case 2: hold = 1; break;
			}
		}
		else if (line[i] == '\'' && (hold == 1 || hold == 3)){
			switch(hold){
			case 1: hold = 3; break;
			case 3: hold = 1; break;
			}
		}
		else {
			char cur[2];
			cur[0] = line[i]; cur[1] = '\0';
			strcat(args[count], cur);
		}
	}
	if (hold == 1){
		count++;
		//used for debugging
		//printArray(args, count);
		detectInput(args, count);
		freeArray(args, count);
	}
	else {
		//if the command has the wrong number of " or '
		fprintf(stderr, "incompatible command\n");
	}
}