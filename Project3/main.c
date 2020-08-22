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
Project #: 3
*/

#define BUFFER 1048
int hold = 1, shell = 1;
pid_t pid = -1;

int jobcount = 0;
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

int changeInput(int argc, char* argV){
	int fstart = 0;
	if (argc == 2){
		if ((fstart = open(argV, O_RDONLY)) == -1){
			printf("Error opening file %s for input\n", argV);
			exit(-1);
		}
		if (dup2(fstart, 0) == -1) {
			perror("dup2");
			exit(EXIT_FAILURE);
		}
	}
	return fstart;
}

int main(int argc, char** argv) {
	if (argc > 2){
		printf("invalid usage: ./P3 [file of commands]\n");
		exit(-1);
	}
	//current implementation of the commands file
	int fstart = changeInput(argc, argv[argc-1]);
	//jobs implementation
	jobsList = (JOB *)malloc(BUFSIZ * sizeof(JOB)); //list of jobs
	//create the log file or erase the file
	FILE* histFile = fopen("blazersh.log", "w");
	char* userInput = malloc(BUFSIZ * sizeof(char));
	while(shell){
		printf("blazersh> ");
		if (fgets(userInput,BUFSIZ,stdin) != NULL){
			if (fstart != 0){
				//print out commands from the file if it was provided
				printf("%s", userInput);
			}
			if (emptyLine(userInput)){
				//write the command to the file if it is not blank/empty
				fwrite(userInput, strlen(userInput), 1, histFile);
				//force write the buffer to the file
				fflush(histFile);
				//fgets keeps the \n so it needs to be removed
				userInput[strlen(userInput) -1] = '\0';
				parseLine(userInput);
			}
		}
		else {
			printf("\rend of file %s\n", argv[1]);
			shell = 0;
		}
	}
	if (fstart != 0){
		close(fstart);
	}
	fclose(histFile);
	return 0;
}