#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

#include "extra.h"

int binarySearch(char **arr, int N, char *search){
	//https://en.wikipedia.org/wiki/Binary_search_algorithm#Procedure
	//made following this psuedocode
	int low = 0;
	int high = N - 1;
	while (high >= low){
		int mid = (high+low)/2;
		if (strcmp(arr[mid], search) > 0){
			high = mid-1;
		}
		else if (strcmp(arr[mid],search) < 0){
			low = mid+1;
		}
		else {
			return mid;
		}
	}
	return -1;
}

void printArray(char **arr, int size){
	int i;
	for (i = 0; i < size; i++){
		printf("%s ", arr[i]);
	} 
}

void insertSort(char **arr, int size) {
	int currLoc, i;
	char *temp = malloc(sizeof(char) * 256);
	for (i = 1; i < size; i++){
		currLoc = i;
		while (currLoc > 0 && strcmp(arr[currLoc], arr[currLoc-1]) < 0 ){
			strcpy(temp,arr[currLoc]);
			stpcpy(arr[currLoc],arr[currLoc - 1]);
			strcpy(arr[currLoc - 1],temp);
			currLoc = currLoc -1;
		}
	}
}

void freeArray(char** arr, int size){
	int i;
	for (i = 0; i < size; i++){
		free(arr[i]);
	}
	free(arr);
}

void writeArray(int fd, char** arr, int size, int index, int offset){
	lseek(fd, offset, SEEK_SET);
	char temp[256];
	int i, length;
	for (i = index; i < size; i++){
		strcpy(temp, arr[i]);
		length=strlen(temp);
		temp[length] = '\n';
		write(fd, temp, length+1);
	}
}