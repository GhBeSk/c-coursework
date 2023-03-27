CC = gcc

demo_shuffle: demo_shuffle.o shuffle.o
	gcc -o demo_shuffle demo_shuffle.o shuffle.o  -lgsl -lgslcblas -lm

single: single.o shuffle.o beggar.o
	gcc -o single single.o shuffle.o beggar.o -lgsl -lgslcblas -lm

byn: byn.o shuffle.o beggar.o
	gcc -o byn byn.o shuffle.o beggar.o -lgsl -lgslcblas -lm

