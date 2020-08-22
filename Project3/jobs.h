#ifndef _JOBS_H_  
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
/*
Name: Samuel Casey
BlazerId: scasey18
Project #: 3
*/

typedef struct job JOB;
struct job{
	int id;
	char* jobName;
};
void printJobList(JOB* jobList);
void addJob(JOB* jobList, int id, char* jobName);
void removeJOB(JOB* jobList, int id);
#endif 