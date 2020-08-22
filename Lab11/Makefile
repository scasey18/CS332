# Sample Makefile to compile C programs 
CC = gcc 
CFLAGS = -Wall -g #replace -g with -O when not debugging 
DEPS     = Makefile 
OBJS     = Lab11.o
EXECS    = Lab11

all:     $(EXECS)

%.o:     %.c $(DEPS) 
		$(CC) $(CFLAGS) -c -o $@ $<  

Lab11: $(OBJS)
		$(CC) $(CFLAGS) -o $@ $^  

clean: 
	/bin/rm -f *.o $(OBJS)