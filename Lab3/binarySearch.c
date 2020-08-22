#include <stdio.h>
#include <stdlib.h>

void printArray(int *arr, int N);
int binarySearch(int *arr, int N, int search);
void sortArray(int *arr, int size);

void printArray(int *arr, int N){
	int i;
	for (i = 0; i < N; i++){
		printf("%d \n", arr[i]);
	}
}

//put it as the array needs to be sorted before the search
void sortArray(int *arr, int size) {
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

int binarySearch(int *arr, int N, int search){
	//https://en.wikipedia.org/wiki/Binary_search_algorithm#Procedure
	//made following this psuedocode
	int low = 0;
	int high = N - 1;
	while (high >= low){
		int mid = (high+low)/2;
		if (arr[mid] > search){
			high = mid-1;
		}
		else if (arr[mid] < search){
			low = mid+1;
		}
		else {
			return mid;
		}
	}
	return -1;
}

int main(int argc, char** argv) {
	int N, i, search;
	printf("Input number of elements in array: ");
	scanf("%d", &N);
	
	int *arr = (int*) malloc(N * sizeof(int)); //make dynamic array
	
	//input array values
	for (i = 0; i < N; i++){
		printf("Element %d: ",i);
		scanf("%d", &arr[i]);
	}
	//Hold number to search for
	printf("Input the number to search for: ");
	scanf("%d", &search);
	printf("Array Given: \n");
	printArray(arr, N);
	sortArray(arr, N); //sort array
	printf("Sorted Array for Search \n");
	printArray(arr, N); //print the array
	
	int res = binarySearch(arr, N, search);
	
	if (res == -1){
		printf("The search value was not found in the given array\n");
	}
	else {
		printf("The search value was found at index %d\n", res); 
	}
	
	free(arr);
	return 0;
}