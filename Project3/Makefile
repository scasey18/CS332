# Sample Makefile to compile C programs 
CC = gcc 
CFLAGS = -Wall -O #replace -g with -O when not debugging 
DEPS     = jobs.h parseLine.h createProcess.h commands.h Makefile 
OBJS     = jobs.o commands.o parseLine.o createProcess.o main.o 
EXECS    = P3

all:     $(EXECS)

%.o:     %.c $(DEPS) 
		$(CC) $(CFLAGS) -c -o $@ $<  

P3: $(OBJS)
		$(CC) $(CFLAGS) -o $@ $^  

clean: 
	/bin/rm -f *.o $(OBJS)