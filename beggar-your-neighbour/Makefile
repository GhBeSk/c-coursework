CC = gcc
CFLAGS = -Wall -Wextra -pedantic -std=c99
LDFLAGS =

all: single byn

single: single.o beggar.o
	$(CC) $(CFLAGS) -o single single.o beggar.o $(LDFLAGS)

byn: byn.o beggar.o
	$(CC) $(CFLAGS) -o byn byn.o beggar.o $(LDFLAGS)

single.o: single.c beggar.h
	$(CC) $(CFLAGS) -c single.c

byn.o: byn.c beggar.h
	$(CC) $(CFLAGS) -c byn.c

beggar.o: beggar.c beggar.h
	$(CC) $(CFLAGS) -c beggar.c

clean:
	rm -f single byn *.o

.PHONY: all clean


