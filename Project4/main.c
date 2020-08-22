#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

#include "parseLine.h"
#include "jobs.h"

/*
Name: Samuel Casey
BlazerId: scasey18
Project #: 4
*/

#define BUFFER 1048
int shell = 1;

int jobcount = 0;
int jobid = 1;
int maxProc, running = 0;
JOB* jobsList;

int emptyLine(char* userLine){
	int i;
	for (i = 0; i < strlen(userLine)-1; i++){
		if (userLine[i] != ' ' && userLine[i] != '\t'){
			return 1;
		}
	}
	return 0;
}

int main(int argc, char** argv) {
	if (argc != 2){
		printf("invalid usage: ./P4 <number of cores> \n");
		exit(-1);
	}
	jobsList = malloc(BUFSIZ * sizeof(JOB));
	char* userInput = malloc(BUFSIZ * sizeof(char));
	if ((maxProc = atoi(argv[1])) == 0 && strcmp(argv[1], "0")){
		printf("Inavlid number of cores given\n");
		exit(-1);
	}
	
	while(shell){
		printf("Enter command> ");
		if (fgets(userInput,BUFSIZ,stdin) != NULL ){
			if (emptyLine(userInput)){
				//fgets keeps the \n so it needs to be removed
				userInput[strlen(userInput) -1] = '\0';
				parseLine(userInput);
			}
		}
	}
	free(userInput);
	return 0;
}