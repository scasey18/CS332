#include <stdio.h>
#include "gettime.h"

int main(int argc, char** argv) {
	int size;
	
	//Retrieve desired size of array
	printf("Input number of elements in array: ");
	scanf("%d", &size);
	int array [size];
	int i;
	
	//Read in elements of array
	for (i = 0; i < size; i++){
		printf("Element %d: ",i);
		scanf("%d", &array[i]);
	}
	// Perform Insertion Sort
	double end;
	double start = gettime();
	printf("Start Time: %f\n",start);
	int temp, currLoc;
	for (i = 1; i < size; i++){
		currLoc = i;
		while (currLoc > 0 && array[currLoc -1] > array[currLoc]){
			temp = array[currLoc];
			array[currLoc] = array[currLoc - 1];
			array[currLoc - 1] = temp;
			currLoc--;
		}
	}
	end = gettime();
	printf("End Time:   %f\n",end);
	printf("Time Taken: %f\n",end-start);
	//Print out the resulting array
	printf("Sorted Array: ");
	for (i = 0; i < size; i++){
		printf("%d ", array[i]);
	}
	printf("\n");
}