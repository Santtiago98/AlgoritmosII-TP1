#MAKEFILE#

#TP N.º 0 – 00
#Algoritmos y Programación II (95.XX) - Facultad de Ingenieria Universidad de Buenos Aires

CFLAGS = -Wall --std=c++11 -g
CC = g++

all: tp1
	rm *.o

tp1: main.o bignum.o cmdline.o shunting_yard.o
	$(CC) $(CFLAGS) -o tp1 cmdline.o bignum.o shunting_yard.o main.o

main.o: main.cc  bignum.h cmdline.h token.hpp shunting_yard.h 
	$(CC) $(CFLAGS) -o main.o -c main.cc 

cmdline.o: cmdline.cc cmdline.h
	$(CC) $(CFLAGS) -o cmdline.o -c cmdline.cc

bignum.o: bignum.cc bignum.h
	$(CC) $(CFLAGS) -o bignum.o -c bignum.cc


shunting_yard.o: shunting_yard.h shunting_yard.cpp stack.hpp 
	$(CC) $(CFLAGS) -o shunting_yard.o -c shunting_yard.cpp
clean: 
	rm *.o


