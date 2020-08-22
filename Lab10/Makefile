# Sample Makefile to compile C programs 
CC = gcc 
CFLAGS = -Wall -g #replace -g with -O when not debugging 
DEPS     = Makefile 
OBJS     = lab10_base.o
EXECS    = Lab10

all:     $(EXECS)

%.o:     %.c $(DEPS) 
		$(CC) $(CFLAGS) -c -o $@ $<  

Lab10: $(OBJS)
		$(CC) $(CFLAGS) -o $@ $^  

clean: 
	/bin/rm -f *.o $(OBJS)