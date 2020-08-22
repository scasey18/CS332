# Sample Makefile to compile C programs 
CC = gcc 
CFLAGS = -Wall -g #replace -g with -O when not debugging 
DEPS     = parseLine.h createProcess.h commands.h Makefile 
OBJS     = commands.o parseLine.o createProcess.o main.o 
EXECS    = P2

all:     $(EXECS)

%.o:     %.c $(DEPS) 
		$(CC) $(CFLAGS) -c -o $@ $<  

P2: $(OBJS)
		$(CC) $(CFLAGS) -o $@ $^  

clean: 
	/bin/rm -f *.o $(OBJS)