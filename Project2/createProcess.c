#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

/*
Name: Samuel Casey
BlazerId: scasey18
Project #: 2
*/

//using function pointers to simplify the process
typedef void func (char** args, int count);

void createProcess(char** args, int count, func myfunc){
	pid_t pid;
	int status;
	
	pid = fork();
	if (pid == 0){
		//child process being made for the desired function
		myfunc(args, count);
	}
	else if (pid > 0){
		//parent process made to wait for the child process
		wait(&status);
	}
	else {
		perror("fork");
		exit(-1);
	}
}