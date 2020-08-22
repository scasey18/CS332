#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

int main(int argc, char** argv) { 
	//This is the implementation of Example 3
	int readFileDescriptor, writeFileDescriptor;
	int n;
	int BUFFSIZE = 4096;
	char buf[BUFFSIZE];
	
	if (argc != 3){ 
		printf("Usage: %s <source> <destination>\n", argv[0]); 
		exit (-1);
	} 
	
	readFileDescriptor = open(argv[1], O_RDONLY); 
	writeFileDescriptor = open(argv[2], O_CREAT|O_WRONLY| O_TRUNC, 0700); 
	
	while ((n=read(readFileDescriptor,buf,BUFFSIZE)) > 0) { 
		if (write(writeFileDescriptor, buf, n) != n){ 
			printf("write error"); 
		} 
	} 
	close(readFileDescriptor); 
	close(writeFileDescriptor); 
	
	//This is the implementation of Example 4
	int SEEKSIZE = -10;
	char lseekMSG[] = "THIS IS NEW MSG FROM LSEEK!\0";
	int RWFileDescriptor;
	
	readFileDescriptor = open(argv[2],O_RDONLY);
	
	if (lseek(readFileDescriptor, SEEKSIZE, SEEK_END) >= 0){ 
		if((n=read(readFileDescriptor,buf,BUFFSIZE)) > 0){ 
			if (write(STDOUT_FILENO, buf, n) != n) { 
				printf("write error"); 
			} 
		} else { 
			printf("read error"); 
		} 
	} else { 
		printf("lseek error"); 
	} 
	printf("\n"); //making sure the output printed on its own line
	RWFileDescriptor = open(argv[2],O_WRONLY);
	if (lseek(RWFileDescriptor, 0, SEEK_SET) >= 0){ 
		if (write(RWFileDescriptor, lseekMSG, strlen(lseekMSG)) != strlen(lseekMSG)) { 
			printf("write error"); 
		} 
	} else { 
		printf("lseek error (During file writing.)"); 
	} 
	close(readFileDescriptor);
	close(RWFileDescriptor); 
	return 0;
}