#include <stdio.h>

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
	//Print out the resulting array
	printf("Sorted Array: ");
	for (i = 0; i < size; i++){
		printf("%d ", array[i]);
	}
	printf("\n");
}