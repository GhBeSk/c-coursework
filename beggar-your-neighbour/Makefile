CC = gcc
CFLAGS = -Wall -Wextra -pedantic -std=c99
LDFLAGS = -lgsl -lgslcblas -lm

all: single byn

single: single.o beggar.o shuffle.o
	$(CC) $(CFLAGS) -o single single.o beggar.o shuffle.o $(LDFLAGS)

byn: byn.o beggar.o shuffle.o
	$(CC) $(CFLAGS) -o byn byn.o beggar.o shuffle.o $(LDFLAGS)

single.o: single.c beggar.h
	$(CC) $(CFLAGS) -c single.c

byn.o: byn.c beggar.h
	$(CC) $(CFLAGS) -c byn.c

beggar.o: beggar.c beggar.h shuffle.h
	$(CC) $(CFLAGS) -c beggar.c

shuffle.o: shuffle.c shuffle.h
	$(CC) $(CFLAGS) -c shuffle.c

clean:
	rm -f *.o single byn



