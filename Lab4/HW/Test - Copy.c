#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

#include "extra.h"

int main(int argc, char** argv) {
	//error handling
	if (argc != 2){
		printf("HW <source file>\n");
		exit(-1);
	}
	//initialize variables
	int readFileDescriptor, n, i, length;
	char buf;
	int size = 10000; //Expected amount of words to sort
	char **arr = (char **) malloc(sizeof(*arr) * size);
	//Step 1
	readFileDescriptor = open(argv[1], O_RDONLY);
	
	for (i = 0; i < size; i++){
		char string[256] = "";
		while((n= read(readFileDescriptor, &buf, 1)) == 1){
			if (buf == '\n'){
				strcat(string, "\0");
				arr[i] = (char *) malloc(sizeof(char) * strlen(string));
				strcpy(arr[i], string);
				break;
			}
			else{
				length = strlen(string);
				string[length] = buf;
			}
		}
	}
	close(readFileDescriptor);
	//printArray(arr, size);
	
	//Step 2
	insertSort(arr,size);
	//printArray(arr, size);
	
	//Step 3
	int RWFileDescriptor;
	char newfile[256] = "";
	strcat(newfile, "Sorted");
	strcat(newfile, argv[1]);
	RWFileDescriptor = open(newfile, O_CREAT|O_RDWR|O_TRUNC, 0777);
	char temp[256];
	for (i = 0; i < size; i++){
		strcpy(temp, arr[i]);
		length=strlen(temp);
		temp[length] = '\n';
		write(RWFileDescriptor, temp, length+1);
	}
	//Step 4
	char key[256];
	printf("Input the key to search for: ");
	scanf("%s", key);
	
	//Step 5
	//Now implement binary search for string character array, and search for given key.   
	int result = binarySearch(arr, size, key);
	if (result != -1){
		printf("Entry Found at Line: %d\n", result+1);
	}
	else{
		printf("Entry not found\n");
		freeArray(arr,size);
		exit(-1);
	}
	
	//Step 6
	char replace[256];
	printf("Input string to replace the key with: ");
	scanf("%s", replace);
	
	//Step 7
	printf("Replacing %s with %s at Line %d\n", key, replace, result+1);
	//Use the lseek function to seek the position of searched key and replace by given string value.  
	lseek(RWFileDescriptor, 0,0);
	int currLine = 0;
	char space = ' ';
	while (read(RWFileDescriptor,&buf,1) > 0){
		if (buf == '\n'){
			currLine++;
		}
		if (currLine == result){
			int curr = lseek(RWFileDescriptor, 0, SEEK_CUR);
			strcat(replace, "\n");
			while ((n = read(RWFileDescriptor, &buf, 1))){
				printf("%c, %d\n",buf, n);
				if(buf != '\n'){
					lseek(RWFileDescriptor, -1,SEEK_CUR);
					write(RWFileDescriptor, &space, 1);
				}
				else if (buf == '\n'){
					lseek(RWFileDescriptor, -1,SEEK_CUR);
					write(RWFileDescriptor, &space, 1);
					break;
				}
			}
			lseek(RWFileDescriptor,curr,SEEK_SET);
			write(RWFileDescriptor,replace,strlen(replace));
			break;
		}
	}
	freeArray(arr, size);
	close(RWFileDescriptor);
	return 0;
}