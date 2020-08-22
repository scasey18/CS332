#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>

/*
Name: Samuel Casey
BlazerId: scasey18
Project #: 2
*/

void list(char** args, int count){
	if (count != 1){
		printf("Invalid syntax for command\n");
		printf("Use help for proper syntax\n");
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
	free(dirent);
	closedir(parentDir);
	exit(0);
}

void help (char** args, int count){
	if (count != 1){
		printf("Invalid syntax for command\n");
		printf("Use help for proper syntax\n");
		exit(-1);
	}
	printf("list     -- this command will list all files in the current working directory\n");
	printf("cd <dir> -- this command will change the current working directory to the dir specified\n");
	printf("help     -- displays a screen with explanations for all included functions of this shell\n");
	printf("history  -- This will print all the previous commands typed into the terminal that were saved to the blazersh.log file\n");
	printf("quit     -- will exit and close the current terminal interface\n");
	exit(0);
}

void cd (char** args, int count){
	if (count < 2){
		printf("Invalid syntax for command\n");
		printf("Use help for proper syntax\n");
	}
	else{
		struct stat buf; char* temp;
		char cwd[1024]; 
		strcpy(cwd, getenv("PWD"));//get the current working directory
		//if args begin with '/' then assume it is a absolute path name
		if (args[1][0] == '/'){
			strcpy(cwd, "/");
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
		printf("Invalid syntax for command\n");
		printf("Use help for proper syntax\n");
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
	args[count] = (char*) NULL;
	chdir(getenv("PWD"));
	execvpe(args[0], args, environ);
	perror("execvpe");
	exit(-1);
}