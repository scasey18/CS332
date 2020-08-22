#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "commands.h"
/*
Name: Samuel Casey
BlazerId: scasey18
Project #: 4
*/

int total;

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
void detectInput(char** args, int count, char* name){
	if (!strcmp("submit", args[0])){
		submitJob(args, count, name);
	}
	else if (!strcmp("showjobs", args[0])){
		//createProcess(args, count, showJobs);
		showJobs(args, count);
	}
	else if (!strcmp("help", args[0])){
		//createProcess(args, count, showHistory);
		help(args, count);
	}
	else{
		printf("invalid command\n");
		printf("run 'help' for commands\n");
	}
}
/**
** Parses the line taken in from the shell to determine the args
**/

int getArgSize(char** args){
	int count = 0;
	while (args[count] != (char*) NULL){
		count++;
	}
	return count;
}

char** argParser(char* line){
	char** args;
	args = malloc(1024 * sizeof(char *)); 
	int count = 0, i;
	char hold = ' ';
	args[count] = malloc(1024 * sizeof(char));
	strcpy(args[count], "\0");
	for (i = 0; i < strlen(line); i++){
		if (line[i] == ' ' && hold == ' '){
			count++;
			args[count] = malloc(1024 * sizeof(char));
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
			sprintf(args[count],"%s%c",args[count], line[i]);
		}
	}
	count++;
	args[count] = (char*) NULL;
	return args;
}

int firstWord(char* line){
	int i;
	for (i = 0; i < strlen(line); i++){
		if (line[i] == ' '){
			return i;
		}
		else if (line[i] == '\0'){
			return 0;
		}
	}
	return -1;
}

void parseLine(char* line){
	char** args = argParser(line);
	int j = firstWord(line);
	int count = getArgSize(args);
	if (j != 0){
		j++;
	}
	if (args != (char**)NULL){
		detectInput(args, count, &line[j]);
		freeArray(args, total);
	}
	else {
		//if the command has the wrong number of " or '
		fprintf(stderr, "incompatible command\n");
		freeArray(args, total);
	}
}