#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "createProcess.h"
#include "commands.h"
/*
Name: Samuel Casey
BlazerId: scasey18
Project #: 3
*/
extern pid_t pid;
extern int shell;
extern int hold;

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
		shell = 0;
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
	else if (!strcmp("jobs", args[0])){
		createProcess(args, count, jobs);
	}
	else if (!strcmp("continue", args[0])){
		createProcess(args, count, contProc);
		pid = atoi(args[1]);
		hold = 1;
		while (hold){
			pause();
		}
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
	int count = 0, i;
	char hold = ' ';
	char cur[2];
	args[count] = malloc(1048 * sizeof(char));
	strcpy(args[count], "\0");
	for (i = 0; i < strlen(line); i++){
		if (line[i] == ' ' && hold == ' '){
			count++;
			args[count] = malloc(1048 * sizeof(char));
			strcpy(args[count], "\0");
		}
		else if (line[i] == '"' || line[i] == '\''){
			if (hold != ' '){
				hold = ' ';
			}
			else {
				hold = line[i];
			}
		}
		else {
			sprintf(cur,"%c", line[i]);
			strcat(args[count], cur);
		}
	}
	if (hold == ' '){
		count++;
		//used for debugging
		//printArray(args, count);
		detectInput(args, count);
		freeArray(args, count);
	}
	else {
		//if the command has the wrong number of " or '
		fprintf(stderr, "incompatible command\n");
		freeArray(args, count);
	}
}