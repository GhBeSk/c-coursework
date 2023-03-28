CC = gcc
CFLAGS = -Wall -Wextra -std=c99

single: single.o shuffle.o beggar.o
	$(CC) $(CFLAGS) -o single single.o shuffle.o beggar.o -lgsl -lgslcblas -lm

byn: byn.o shuffle.o beggar.o
	$(CC) $(CFLAGS) -o byn byn.o shuffle.o beggar.o -lgsl -lgslcblas -lm

single.o: single.c beggar.h shuffle.h
	$(CC) $(CFLAGS) -c single.c

byn.o: byn.c beggar.h shuffle.h
	$(CC) $(CFLAGS) -c byn.c

shuffle.o: shuffle.c shuffle.h
	$(CC) $(CFLAGS) -c shuffle.c

beggar.o: beggar.c beggar.h
	$(CC) $(CFLAGS) -c beggar.c

clean:
	rm -f single byn *.o


