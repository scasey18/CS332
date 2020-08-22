#ifndef _EXTRA_H_  
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
void printArray(char **arr, int size);
void insertSort(char **arr, int size);
int binarySearch(char **arr, int N, char *search);
void freeArray(char** arr, int size);
void writeArray(int fd, char** arr, int size, int index, int offset);
#endif 