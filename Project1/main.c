#include <stdio.h> 
#include <stdlib.h>
#include <string.h>

#include "fileop.h"
/*
Name: Samuel Casey
BlazerId: scasey18
Project #: 1
*/
void error();

//Global variables to reduce the args needed to pass to other functions in this project
int minsize = 0; //minimum file size
char* searchString; //string to check for in filenames

//This main serves as the parser for the arguments given by the user
int main(int argc, char** argv) {
	int str=0, size=0, i; //set pointers to identify portions of the arguments
	char fn[strlen(argv[argc-1])+1]; //create a string for path of atleast length of last argument
	for (i = 1; i < argc; i++){ //iterate through ignoring the function call
		if (!strcmp(argv[i],"-s")){ //identify the position of argument
			//make sure size is not already given and -f does not follow immediately
			if (strcmp(argv[i+1],"-f") != 0 && size == 0){
				i++;
				size = i;
			}
			else {
				error(); //error if anything fishy with argument positions
			}
		}
		else if (!strcmp(argv[i],"-f")){
			if (strcmp(argv[i+1],"-s") != 0 && str == 0){
				i++;
				str = i;
			}
			else {
				error();
			}
		}
		//catch any floating arguments that dont belong
		else if (i != argc-1){
			error();
		}
	}
	//default, will always run the filename as true
	if (str == 0){ 
		searchString = "";
	}
	//set searchString to that file
	else{ 
		searchString = argv[str];
	}
	//set minsize to the size specified
	if (size != 0){ 
		minsize = atoi(argv[size]);
	}
	//check if pos is taken and if so then give default location 
	if (argc-1 == size || argc-1 == str){ 
		strcpy(fn, ".");
	}
	else { //else get the filepath from that directory
		strcpy(fn,argv[argc-1]);
	}
	 //print inital directory name
	printf("%s\n", fn); 
	if (fn[strlen(fn) -1] != '/'){
		strcat(fn, "/"); //add this to indicate it as a directory if not there already
	}
	printDIR(fn,0, printResult); //call function
}

//print error if found in the user specification
void error(){
	printf("Invalid syntax: ./P1 [-f] <string to search> [-s] <minimum number of bytes> [directory]\n");
	exit(-1);
}