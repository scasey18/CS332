#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <signal.h>

#include "jobs.h"
/*
Name: Samuel Casey
BlazerId: scasey18
Project #: 3
*/

extern JOB* jobsList;

void list(char** args, int count){
	if (count != 1){
		fprintf(stderr,"Invalid syntax for command\n");
		fprintf(stderr,"Use help for proper syntax\n");
		exit(-1);
	}
	struct dirent *dirent; 
	DIR *parentDir;
	char* cwd = getenv("PWD");
	parentDir = opendir (cwd); 
	if (parentDir == NULL) { 
		printf ("Error opening directory '%s'\n", cwd); 
		exit (-1);
	}
	while((dirent = readdir(parentDir)) != NULL){
		if (strcmp((*dirent).d_name,".") && strcmp((*dirent).d_name,"..")){
			printf ("%s\n",(*dirent).d_name); 
		}
	}
	fflush(stdout);
	free(dirent);
	closedir(parentDir);
	exit(0);
}

void help (char** args, int count){
	if (count != 1){
		fprintf(stderr,"Invalid syntax for command\n");
		fprintf(stderr,"Use help for proper syntax\n");
		exit(-1);
	}
	printf("list     -- this command will list all files in the current working directory\n");
	printf("cd <dir> -- this command will change the current working directory to the dir specified\n");
	printf("help     -- displays a screen with explanations for all included functions of this shell\n");
	printf("history  -- This will print all the previous commands typed into the terminal that were saved to the blazersh.log file\n");
	printf("jobs     -- Print list of programs that are stopped (Control-Z)\n");
	printf("continue <pid> -- start a process that has been stopped already. Run jobs to see those avaliable\n");
	printf("quit     -- will exit and close the current terminal interface\n");
	fflush(stdout);
	exit(0);
}

void cd (char** args, int count){
	if (count < 2 || count == 1){
		fprintf(stderr,"Invalid syntax for command\n");
		fprintf(stderr,"Use help for proper syntax\n");
	}
	else{
		struct stat buf; char* temp;
		char * cwd = (char *) malloc (1024 * sizeof(char)); 
		//if args begin with '/' then assume it is a absolute path name
		if (args[1][0] == '/'){
			strcpy(cwd, "/");
		}
		else {
			strcpy(cwd, getenv("PWD"));//get the current working directory
		}
		temp = strtok(args[1], "/");
		while (temp != NULL){
			if (!strcmp(temp, ".")){
				//do nothing as it is already the same directory
			}
			else if (!strcmp(temp, "..")){
				int i;
				for (i = strlen(cwd); i > 0; i--){
					if (i == 1 || cwd[i] == '/'){
						cwd[i] = '\0';
						break;
					}
				}
			}
			else{
				if (cwd[strlen(cwd)-1] != '/'){
					strcat(cwd, "/");
				}
				strcat(cwd, temp);
			}
			temp = strtok(NULL, "/");
		}
		//This checks if the location exists and if the location is a folder then set the pwd
		if (lstat(cwd, &buf) == 0 && S_ISDIR(buf.st_mode) != 0){
			if (setenv("PWD", cwd, 1) < 0){
				perror("setenv");
			}
		}
		else {
			printf("invalid directory path provided\n");
		}
	}
}

void history (char** args, int count){
	if (count != 1){
		fprintf(stderr,"Invalid syntax for command\n");
		fprintf(stderr,"Use help for proper syntax\n");
		exit(-1);
	}
	FILE* hist = fopen("blazersh.log", "r");
	char buffer[1048];
	while(fgets(buffer, sizeof(buffer), hist) >0){
		printf("%s", buffer);
	}
	fclose(hist);
	exit(0);
}

void otherFuncs(char** args, int count){
	args[count] = NULL;
	if(chdir(getenv("PWD")) == -1){
		perror("chdir");
		exit(-1);
	}
	execvp(args[0], args);
	perror("execvp");
	exit(-1);
}

void contProc(char** args, int count){
	if (count != 2){
		fprintf(stderr,"Invalid syntax for command\n");
		fprintf(stderr,"Use help for proper syntax\n");
		exit(-1);
	}
	if (kill(atoi(args[1]), SIGCONT) == -1){
		perror("kill");
		exit(-1);
	}
	exit(0);
}

void jobs(char** args, int count){
	printJobList(jobsList);
	exit(0);
}