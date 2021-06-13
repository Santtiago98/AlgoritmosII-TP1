#MAKEFILE#

#TP N.º 0 – 00
#Algoritmos y Programación II (95.XX) - Facultad de Ingenieria Universidad de Buenos Aires

CFLAGS = -Wall --std=c++11
CC = g++


all: tp1.exe
	rm *.o

tp1.exe: main.o bignum.o cmdline.o token.o shunting_yard.o
	$(CC) $(CFLAGS) -o tp1.exe cmdline.o bignum.o token.o main.o

main.o: main.cc  bignum.h cmdline.h token.cpp stack.hpp 
	$(CC) $(CFLAGS) -o main.o -c main.cc 

cmdline.o: cmdline.cc cmdline.h
	$(CC) $(CFLAGS) -o cmdline.o -c cmdline.cc

bignum.o: bignum.cc bignum.h
	$(CC) $(CFLAGS) -o bignum.o -c bignum.cc

token.o: token.cpp 
	$(CC) $(CFLAGS) -o token.o -c token.cpp
    
clean: 
	rm *.o


