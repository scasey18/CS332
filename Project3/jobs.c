#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern int jobcount;
typedef struct job JOB;

struct job{
	int id;
	char jobName[BUFSIZ];
};

void printJobList(JOB* jobList){
	printf("PID\tName\n");
	int i;
	for (i = 0; i < jobcount; i++){
		printf("%d\t%s\n", jobList[i].id, jobList[i].jobName);
	}
}

void addJob(JOB* jobList, int id, char* jobName){
	jobList[jobcount].id = id;
	strcpy(jobList[jobcount].jobName, jobName);
	jobcount++;
}

void removeJOB(JOB* jobList, int id){
	int i, j = 0;
	for (i = 0; i < jobcount; i++){
		if (jobList[i].id == id){
			j = 1;
		}
		if (j){
			jobList[i] = jobList[i+1];
		}
	}
	if (j){
		jobcount--;
	}
}