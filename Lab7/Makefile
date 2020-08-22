# Sample Makefile to compile C programs 
CC = gcc 
CFLAGS = -Wall -O #replace -g with -O when not debugging 
DEPS     = Makefile 
OBJS     = main.o 
EXECS    = HW

all:     $(EXECS) 

%.o:     %.c $(DEPS) 
		$(CC) $(CFLAGS) -c -o $@ $<  

HW: $(OBJS)
		$(CC) $(CFLAGS) -o $@ $^  

clean: /bin/rm -i *.o $(EXECS) 