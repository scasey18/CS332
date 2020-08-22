# Sample Makefile to compile C programs 
CC = gcc 
CFLAGS = -Wall -g -pthread #replace -g with -O when not debugging 
DEPS     = Makefile 
OBJS     = Lab13.o
EXECS    = Lab13

all:     $(EXECS)

%.o:     %.c $(DEPS) 
		$(CC) $(CFLAGS) -c -o $@ $<  

Lab13: $(OBJS)
		$(CC) $(CFLAGS) -o $@ $^  

clean: 
	/bin/rm -f *.o $(OBJS)