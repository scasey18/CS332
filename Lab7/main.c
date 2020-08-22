#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <string.h>

#define BUFFER 1024

void freeArray(char** args, int count){
	int i;
	for (i = 0; i < count; i++){
		free(args[i]);
	}
	free(args);
}

void execLine(char** args, int count, FILE *outfd){
	int status, i;
	pid_t pid;
	
	pid = fork();
	if (pid == 0){
		execvp(args[0], args);
		perror("exec");
		exit(-1);
	}
	else if (pid > 0){
		time_t endtime; time_t curtime = time(NULL);
		wait(&status);
		endtime = time(NULL);
		if (WIFEXITED(status)){
			for (i = 0; i < count-1; i++){
				fprintf(outfd, "%s ", args[i]);
			}
			fprintf(outfd, "%s", args[count-1]);
			char string[BUFFER]; 
			strcpy(string, ctime(&curtime));
			if (string[strlen(string)-1] == '\n')
				string[strlen(string)-1] = '\0';
			fprintf(outfd,"\t%s\t%s", string, ctime(&endtime));
		}
		else{
			printf("Child process exited incorrectly\n");
		}
	}
	else{
		perror("fork"); 
		exit(EXIT_FAILURE);
	}
	
}

int main(int argc, char **argv) {
	if (argc != 2){
		printf("Invalid Syntax: %s <filename>\n", argv[0]);
		exit(-1);
	}
	FILE *srcfd = fopen(argv[1], "r"); //open the provided file
	FILE *outfd = fopen("output.log", "w"); //create/truncate the default output file
	char line[BUFFER];
	while(fgets(line, BUFFER,srcfd) != NULL){
		//extra \n causes problems for the execvp execution so replace it with null character
		if (line[strlen(line)-1] == '\n'){
			line[strlen(line)-1] = '\0';
		}
		char* temp; char **args = malloc(BUFFER * sizeof(char *)); 
		int count = 0;
		temp = strtok(line, " ");
		printf("Executing ");
		while(temp != NULL){
			args[count] = malloc(strlen(temp)+1 * sizeof(char));
			strcpy(args[count], temp);
			printf("%s ", args[count]);
			count++;
			temp = strtok(NULL, " ");
		}
		printf("as a child process\n");
		args[count] = (char*)NULL;
		execLine(args, count, outfd);
		freeArray(args, count);
	}
	fclose(srcfd);
	fclose(outfd);
	return 0;
}