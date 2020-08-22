#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define max(x,y) (((x) >= (y)) ? (x) : (y))

extern int jobcount;
extern int jobid;
typedef struct job JOB;

struct job{
	int id;
	char jobName[BUFSIZ];
	char status[BUFSIZ];
	int pid;
};

void printJobList(JOB* jobList){
	int i, lid = 2, lname= 4;
	char temp[BUFSIZ];
	for (i = 0; i < jobcount; i++){
		sprintf(temp,"%d", jobList[i].id);
		if (strlen(temp) > lid){
			lid = strlen(temp);
		}
		if (strlen(jobList[i].jobName) > lname){
			lname = strlen(jobList[i].jobName);
		}
	}
	char spaces[max(lname,lid)];
	//make spaces for formatting purposes with the max of the two values
	for (i = 0; i < max(lname,lid); i++)
		strcat(spaces, " ");
	
	int idspacing = strlen(spaces) - lid;
	int namespacing = strlen(spaces) - lname;
	printf("ID%s   Name%s   Status\n", &spaces[idspacing + strlen("ID")], &spaces[namespacing + strlen("Name")]);
	for (i = 0; i < jobcount; i++){
		sprintf(temp,"%d", jobList[i].id);
		printf("%d%s   ", jobList[i].id, &spaces[idspacing + strlen(temp)]);
		printf("%s%s   ", jobList[i].jobName, &spaces[namespacing + strlen(jobList[i].jobName)]);
		printf("%s\n", jobList[i].status);
	}
}

void setPID(JOB* jobList, int jobid, int pid){
	int i;
	for (i = 0; i < jobcount; i++){
		if (jobList[i].id == jobid){
			jobList[i].pid = pid;
			strcpy(jobList[i].status, "Running");
			break;
		}
	}
}

void addJob(JOB* jobList, char* jobName){
	jobList[jobcount].id = jobid;
	strcpy(jobList[jobcount].jobName, jobName);
	strcpy(jobList[jobcount].status, "Waiting");
	jobcount++;
	jobid++;
}

void removeJOB(JOB* jobList, int id){
	int i, j = 0;
	for (i = 0; i < jobcount; i++){
		if (jobList[i].pid == id){
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

void freeJOBS(JOB* jobList, int count){
	int i;
	for (i = 0; i < count; i++){
		free(&jobList[i]);
	}
	free(jobList);
}