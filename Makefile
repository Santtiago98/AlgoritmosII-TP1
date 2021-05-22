#MAKEFILE#

#TP N.º 0 – 00
#Algoritmos y Programación II (95.XX) - Facultad de Ingenieria Universidad de Buenos Aires

CFLAGS = -Wall --std=c++11
CC = g++


all: tp0.exe


tp0.exe: main.o bignum.o cmdline.o
	$(CC) $(CFLAGS) -o tp0.exe cmdline.o bignum.o main.o

main.o: main.cc  bignum.h cmdline.h
	$(CC) $(CFLAGS) -o main.o -c main.cc

cmdline.o: cmdline.cc cmdline.h
	$(CC) $(CFLAGS) -o cmdline.o -c cmdline.cc

bignum.o: bignum.cc bignum.h
	$(CC) $(CFLAGS) -o bignum.o -c bignum.cc


clean: 
	rm *.o


