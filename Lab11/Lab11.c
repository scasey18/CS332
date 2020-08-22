#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>

void pipeOP(char* uInput){
	FILE *fp2;
	
	if ((fp2 = popen(uInput, "w")) == NULL) {
		perror("popen");
		exit(EXIT_FAILURE);
	}
	
	if (pclose(fp2) == -1) {
		perror("pclose");
		exit(EXIT_FAILURE);
	}
}


int main(int argc, char **argv) {
	int hold = 1; char uInput[BUFSIZ];
	while (hold){
		printf("Enter a command: ");
		fgets(uInput, BUFSIZ, stdin);
		uInput[strlen(uInput)-1] = '\0';
		if (!strcmp(uInput, "quit")){
			hold = 0;
		}
		else {
			pipeOP(uInput);
		}
	}
	return 0;
}