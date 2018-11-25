PROG = main
CC = g++
CPPFLAGS = -Wall -O2
OBJS = main.o test.o

$(PROG) : $(OBJS)
	$(CC) -o $(PROG) $(OBJS) 

main.o :
	$(CC) $(CPPFLAGS) -c main.cpp

test.o : test.hpp
	$(CC) $(CPPFLAGS) -c test.cpp

clean :
	rm -f core $(PROG) $(OBJS)