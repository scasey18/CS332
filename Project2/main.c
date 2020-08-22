#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "parseLine.h"
/*
Name: Samuel Casey
BlazerId: scasey18
Project #: 2
*/

#define BUFFER 1048


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
	if (argc != 1){
		printf("invalid usage: no arguments should be provided to this program\n");
		exit(-1);
	}
	//create the log file or erase the file
	FILE* histFile = fopen("blazersh.log", "w");
	while(1){
		char userInput[BUFFER] = "\0";
		printf("blazersh> ");
		fgets(userInput,BUFFER,stdin);
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
	fclose(histFile);
	return 0;
}