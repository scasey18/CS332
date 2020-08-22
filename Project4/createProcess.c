#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <string.h>
#include <fcntl.h>
#include <signal.h>

#include "parseLine.h"
#include "commands.h"
#include "jobs.h"
/*
Name: Samuel Casey
BlazerId: scasey18
Project #: 4
*/

#define INPUT  "<"
#define OUTPUT ">"
#define stdout1 ".out"
#define stderr1 ".err"

//using function pointers to simplify the process
typedef void func (char** args, int count);

pid_t pid;
int status, fdin, fdout, fderr;
extern int jobid, jobcount, maxProc, running, shell;
extern JOB* jobsList;

void createProcess(char** args, int count,char* name, int id);

int determinePath(char** args, int count, char* check){
	int i;
	for (i = 0; i < count; i++){
		if (!strcmp(check, args[i])){
			//cannot have a file if it is last argument
			if (i == count - 1){
				return -1;
			}
			return i+1;
		}
	}
	return 0;
}

int changeOutput(char** args, int count, char* check, int jobid){
	int val = determinePath(args, count, check);
	if (val == -1){
		fprintf(stderr,"error: no file given after %s\n", check);
		exit(-1);
	}
	char out[BUFSIZ];
	sprintf(out,"%d%s",jobid,stdout1);
	//will only create a output file of the first for a regular process
	if ((fdout = open(out, O_CREAT| O_WRONLY, 0755)) == -1){
		printf("Error opening file %s for input\n", args[val]);
		exit(-1);
	}
	if (dup2(fdout, 1) == -1) {
		perror("dup2");
		exit(EXIT_FAILURE);
	}
	sprintf(out,"%d%s",jobid,stderr1);
	if ((fderr = open(out, O_CREAT| O_WRONLY, 0755)) == -1){
		printf("Error opening file %s for input\n", args[val]);
		exit(-1);
	}
	if (dup2(fderr, 2) == -1) {
		perror("dup2");
		exit(EXIT_FAILURE);
	}
	if (val == 0){
		return count;
	}
	return val;
}

int changeInput(char** args, int count, char* check){
	int val = determinePath(args, count, check);
	if (val == -1){
		fprintf(stderr,"error: no file given after %s\n", check);
		exit(-1);
	}
	if (val == 0){
		return count;
	}
	if ((fdin = open(args[val], O_RDONLY)) == -1){
		printf("Error opening file %s for input\n", args[val]);
		exit(-1);
	}
	if (dup2(fdin, 0) == -1) {
		perror("dup2");
		exit(EXIT_FAILURE);
	}
	return val;
}

void sigchild(int signo){
	int temp = wait(&status);
	fflush(stdout);
	removeJOB(jobsList, temp);
	//the child process should not return anything so kill it
	running--;
	if (running < jobcount){
		int i;
		for (i = 0; i < jobcount; i++){
			if (jobsList[i].pid == 0){
				//Run the next command
				char** args = argParser(jobsList[i].jobName);
				int count = getArgSize(args);
				createProcess(args, count , jobsList[i].jobName, jobsList[i].id+1);
				freeArray(args, count);
				break;
			}
		}
	}
	signal(SIGCHLD, sigchild);
}

void sigpar(int signo){
	int i;
	printf("\n");
	for (i = 0; i < jobcount; i++){
		if(jobsList[i].pid != 0){
			printf("[%d]: Killing Job #%d\n", jobsList[i].pid, jobsList[i].id);
			kill(jobsList[i].pid, SIGINT);
		}
		else {
			printf("Removing Job #%d\n", jobsList[i].id);
		}
	}
	printf("Exiting Job Scheduler...\n");
	exit(0);
}

void createProcess(char** args, int count,char* name, int id){
	
	pid = fork();
	if (pid == 0){
		//child process being made for the desired function
		//changes the IO if needed
		int input = changeInput(args, count, INPUT);
		int output = changeOutput(args, count, OUTPUT, id-1);
		//reduce count to make sure that the function does not recieve
		//these unneeded parameters
		if (count > input){
			count = input-1;
		}
		if (count > output){
			count = output-1;
		}
		args[count] = (char*)NULL;
		otherFuncs(args, count);
	}
	else if (pid > 0){
		//parent process made to wait for the child process
		setPID(jobsList, id-1, pid);
		//printArray(args, count);
		if (signal(SIGINT, sigpar) == SIG_ERR){
			printf("Unable to catch SIGINT\n");
		}
		if (signal(SIGCHLD, sigchild) == SIG_ERR) {
			printf("Unable to catch SIGCHLD\n");
		}
	}
	else {
		perror("fork");
		exit(-1);
	}
}