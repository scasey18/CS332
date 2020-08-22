#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "jobs.h"
#include "createProcess.h"
/*
Name: Samuel Casey
BlazerId: scasey18
Project #: 4
*/

extern JOB* jobsList;
extern int jobcount, jobid, maxProc, running;

void otherFuncs(char** args, int count){
	if(chdir(getenv("PWD")) == -1){
		perror("chdir");
		exit(-1);
	}
	execvp(args[0], args);
	perror("execvp");
	exit(-1);
}

void help(char** args, int count){
	printf("showjobs     : List all jobs currently running or waiting to be run\n");
	printf("submit <job> : Submits the job to be run in order\n");
	printf("help         : Displays a screen with included commands and syntax\n");
}

void showJobs(char** args, int count){
	printJobList(jobsList);
}

void submitJob(char** args, int count,char* name){
	addJob(jobsList, name);
	printf("Job #%d has been added to the list\n", jobid-1);
	if (running < maxProc){
		createProcess(&args[1], count-1, name, jobid);
		running++;
	}
}