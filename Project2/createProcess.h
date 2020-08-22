#ifndef _CREATEPROCESS_H_  
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
/*
Name: Samuel Casey
BlazerId: scasey18
Project #: 2
*/
typedef void func (char** args, int count);

void createProcess(char** args, int count, func myfunc);
#endif 