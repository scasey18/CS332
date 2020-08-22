/* Simple program to illustrate the use of fork-exec-wait pattern. 
* This version uses execvp and command-line arguments to create a new process.
* To Compile: gcc -Wall forkexecvp.c
* To Run: ./a.out <command> [args]
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

pid_t pid;

static void sig_int(int signo){
	int status;
	if (signo == SIGINT){
		printf(" SIGINT %d\n", pid);
		kill(pid, SIGINT);
	}
	if (signo == SIGTSTP){
		printf(" SIGTSTP %d\n", pid);
		kill(pid, SIGTSTP);
	}
	waitpid(pid, &status, WNOHANG); /* wait for the child process to terminate */
	if (WIFEXITED(status)) { /* child process terminated normally */
		printf("Child process exited with status = %d\n", WEXITSTATUS(status));
	} else { /* child process did not terminate normally */
		printf("Child process did not terminate normally!\n");
		/* look at the man page for wait (man 2 wait) to determine
			how the child process was terminated */
	}
}

int main(int argc, char **argv) {

	if (argc < 2) {
		printf("Usage: %s <command> [args]\n", argv[0]);
		exit(-1);
	}

	pid = fork();
	if (pid == 0) { /* this is child process */
		execvp(argv[1], &argv[1]);
		printf("If you see this statement then execl failed ;-(\n");
		exit(-1);
	} else if (pid > 0) { /* this is the parent process */
		printf("Wait for the child process to terminate\n");
		if (signal(SIGINT, sig_int) == SIG_ERR) {
			printf("Unable to catch SIGINT\n");
		}
		if (signal(SIGTSTP, sig_int) == SIG_ERR) {
			printf("Unable to catch SIGSTP\n");
		}
		for(;;){
			pause();
		}
	}
	else { /* we have an error */
		perror("fork"); /* use perror to print the system error message */
		exit(EXIT_FAILURE);
	}

	printf("[%ld]: Exiting program .....\n", (long)getpid());

	return 0;
}
