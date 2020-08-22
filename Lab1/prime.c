#include <stdio.h>
#include <stdbool.h>

//This was written using the palindrome example as a base given by
//Dr. Bangalore

bool isPrime(int given_number) {
	int i;
	//not checking 0 or 1 since they are not prime
	if (given_number <= 1){
		return false;
	}
	//no reason to check after 1/2 of the given number
	for (i = 2; i <= given_number/2; i++) {
		//check if division remainder is 0 then it is prime
		if (given_number % i == 0) {
			return false;
		}
	}
	return true;
}

int main(int argc, char** argv) {
	int given_number; //intialize variables

	printf("Enter a number: "); //Prompt for input
	scanf("%d", &given_number); //recieve input to variable

	if (isPrime(given_number)) { //perform action based on result
		printf("%d is prime\n", given_number);
		//printf("The number is prime\n");
	}
	else {
		printf("%d is not prime\n", given_number);
		//printf("The number is not prime\n");
	}

	return 0;
}