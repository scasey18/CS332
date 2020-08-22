#include <stdio.h>
#include <stdlib.h>

void displayArray(float *arr, int size); 
void sortArray(float *arr, int size); 

void displayArray(float *arr, int size){ 
    int i;
	printf("["); 
    for (i=0; i<size-1; i++) { 
            printf("%f, ",arr[i]); 
    } 
    printf("%f]\n", arr[size-1]);      
}

void sortArray(float *arr, int size) {
	int temp, currLoc, i;
	for (i = 1; i < size; i++){
		currLoc = i;
		while (currLoc > 0 && arr[currLoc -1] > arr[currLoc]){
			temp = arr[currLoc];
			arr[currLoc] = arr[currLoc - 1];
			arr[currLoc - 1] = temp;
			currLoc--;
		}
	}
}

int main(int argc, char** argv) {
	int N, i;
	
	//Retrieve desired size of array
	printf("Input number of elements in array: ");
	scanf("%d", &N);
	
	float *arr = (float*) malloc(N * sizeof(float)); 
	
	for (i = 0; i < N; i++){
		printf("Element %d: ",i);
		scanf("%e", &arr[i]);
	}
	
	sortArray(arr, N); 
	displayArray(arr, N); 
	
	free(arr);
	
	return 0;
}