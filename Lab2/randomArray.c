#include <stdlib.h> 
#include <stdio.h>
#include <time.h> 

#define size 100 

int main(int argc, char** argv) {
	srand48((unsigned int)time(NULL)); 
	double array [size]; 
	
	int i;
	
	for (i=0; i<size; i++) { 
		array[i] = drand48(); 
		printf("%f ", array[i]);
	} 
	
	double min_value = array[0]; 

	for (i=0; i<size; i++) { 
		if (array[i] < min_value) { 
			min_value = array[i]; 
		} 
	} 
	printf("\nMin Value: %f \n", min_value);
}