#ifndef _CREATEPROCESS_H_  
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <string.h>
#include <signal.h>
/*
Name: Samuel Casey
BlazerId: scasey18
Project #: 3
*/
typedef void func (char** args, int count);

void createProcess(char** args, int count, func myfunc);
#endif 