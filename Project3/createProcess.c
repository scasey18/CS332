#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <string.h>
#include <fcntl.h>
#include <signal.h>

#include "jobs.h"
/*
Name: Samuel Casey
BlazerId: scasey18
Project #: 3
*/

#define INPUT  "<"
#define OUTPUT ">"

//using function pointers to simplify the process
typedef void func (char** args, int count);

extern pid_t pid;
int status, fdin, fdout;
char* name;
extern int hold;
extern JOB* jobsList;

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

int changeIO(char** args, int count, char* check, int choice){
	int val = determinePath(args, count, check);
	if (val == -1){
		fprintf(stderr,"error: no file given after %s\n", check);
		exit(-1);
	}
	else if (val != 0){
		//makes the file selection much easier
		if(chdir(getenv("PWD")) == -1) {
			perror("chdir");
			exit(-1);
		}
		if (choice == 0){
			if ((fdin = open(args[val], O_RDONLY)) == -1){
				printf("Error opening file %s for input\n", args[val]);
				exit(-1);
			}
			if (dup2(fdin, choice) == -1) {
				perror("dup2");
				exit(EXIT_FAILURE);
			}
		}
		else if (choice == 1){
			if ((fdout = open(args[val], O_CREAT| O_WRONLY, 0755)) == -1){
				printf("Error opening file %s for input\n", args[val]);
				exit(-1);
			}
			if (dup2(fdout, choice) == -1) {
				perror("dup2");
				exit(EXIT_FAILURE);
			}
		}
		return val;
	}
	return count;
}

void sigchild(int signo){
	waitpid(pid, &status, WNOHANG);
	hold = 0;
	fflush(stdout);
	if (signo != SIGTSTP){
		removeJOB(jobsList, pid);
	}
	//the child process should not return anything so kill it
	signal(SIGCHLD, sigchild);
}

void sigpar(int signo){
	if (pid != -1){
	if (signo == SIGINT){
		printf("[%d] : Interrupted\n", pid);
		kill(pid, signo);
	}
	else if (signo == SIGTSTP){
		printf("[%d] : Stopped\n", pid);
		addJob(jobsList, pid, name);
		kill(pid, signo);
	}
	signal(SIGINT, sigpar);
	signal(SIGTSTP, sigpar);
	}
}

void createProcess(char** args, int count, func myfunc){
	
	pid = fork();
	if (pid == 0){
		//child process being made for the desired function
		//changes the IO if needed
		int input = changeIO(args, count, INPUT, 0);
		int output = changeIO(args, count, OUTPUT, 1);
		//reduce count to make sure that the function does not recieve
		//these unneeded parameters
		if (count > input){
			count = input-1;
		}
		if (count > output){
			count = output-1;
		}
		args[count] = (char*)NULL;
		myfunc(args, count);
	}
	else if (pid > 0){
		//parent process made to wait for the child process
		hold = 1;
		name = args[0];
		if (signal(SIGINT, sigpar) == SIG_ERR){
			printf("Unable to catch SIGINT\n");
		}
		if (signal(SIGTSTP, sigpar) == SIG_ERR){
			printf("Unable to catch SIGTSTP\n");
		}
		if (signal(SIGCHLD, sigchild) == SIG_ERR) {
			printf("Unable to catch SIGCHLD\n");
		}
		while (hold){
			pause();
		}
		pid = -1;
	}
	else {
		perror("fork");
		exit(-1);
	}
}