CS332 Project 1:

Makefile: Used to compile the project
main.c: used to initally call the function and perform argument parser of the entire program
fileop.c: holds the main functions to iterate through the file hierarchy and print out appropriate information
printops.c: holds the file print functions for each file type specified in the project

#Compile and Run:
Use the make file for the makefile utility to create the ./P1 executable
run this executable using this structure

./P1 [-f] <string to search> [-s] <minimum number of bytes> [directory]

Do to the use of atoi. any string that is not a number after -s will result in a value of 0.