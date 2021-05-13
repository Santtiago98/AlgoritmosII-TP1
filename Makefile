
#MAKEFILE#

#TP N.º 0 – 00
#Algoritmos y Programación II (95.XX) - Facultad de Ingenieria Universidad de Buenos Aires

CFLAGS = -Wall --std=c++11
CC = g++


all: tp0 clean


tp0: main.o bignum.o 
	$(CC) $(CFLAGS) -o tp0 main.o bignum.o


main.o: main.cc  bignum.h 
	$(CC) $(CFLAGS) -o main.o -c main.cc

bignum.o: bignum.cc
	$(CC) $(CFLAGS) -o bignum.o -c bignum.cc


clean: 
	rm *.o


