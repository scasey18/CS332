# Sample Makefile to compile C programs 
CC = gcc 
CFLAGS = -Wall -g #replace -g with -O when not debugging 
DEPS     = printops.h fileop.h Makefile 
OBJS     = printops.o fileop.o main.o 
EXECS    = P1

all:     $(EXECS) 

%.o:     %.c $(DEPS) 
		$(CC) $(CFLAGS) -c -o $@ $<  

P1: $(OBJS)
		$(CC) $(CFLAGS) -o $@ $^  

clean: /bin/rm -i *.o $(EXECS) 