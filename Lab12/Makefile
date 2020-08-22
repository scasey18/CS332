# Sample Makefile to compile C programs 
CC = gcc 
CFLAGS = -Wall -g -pthread #replace -g with -O when not debugging 
DEPS     = Makefile 
OBJS     = Lab12.o
EXECS    = Lab12

all:     $(EXECS)

%.o:     %.c $(DEPS) 
		$(CC) $(CFLAGS) -c -o $@ $<  

Lab12: $(OBJS)
		$(CC) $(CFLAGS) -o $@ $^  

clean: 
	/bin/rm -f *.o $(OBJS)