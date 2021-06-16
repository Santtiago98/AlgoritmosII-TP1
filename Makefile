#MAKEFILE#

#TP N.º 0 – 00
#Algoritmos y Programación II (95.XX) - Facultad de Ingenieria Universidad de Buenos Aires

CFLAGS = -Wall --std=c++11 -g
CC = g++

all: tp1
	rm *.o

tp1: main.o bignum.o cmdline.o shunting_yard.o standard_multiply.o karatsuba.o
	$(CC) $(CFLAGS) -o tp1 cmdline.o bignum.o shunting_yard.o standard_multiply.o karatsuba.o main.o

main.o: main.cc  bignum.h cmdline.h token.hpp shunting_yard.h strategy.h standard_multiply.h karatsuba.h
	$(CC) $(CFLAGS) -o main.o -c main.cc 

cmdline.o: cmdline.cc cmdline.h
	$(CC) $(CFLAGS) -o cmdline.o -c cmdline.cc

bignum.o: bignum.cc bignum.h strategy.h
	$(CC) $(CFLAGS) -o bignum.o -c bignum.cc 

shunting_yard.o: shunting_yard.h stack.hpp 
	$(CC) $(CFLAGS) -o shunting_yard.o -c shunting_yard.cpp

standard_multiply.o: standard_multiply.h bignum.h strategy.h
	$(CC) $(CFLAGS) -o standard_multiply.o -c standard_multiply.cpp

karatsuba.o: karatsuba.h bignum.h strategy.h
	$(CC) $(CFLAGS) -o karatsuba.o -c karatsuba.cpp 

clean: 
	rm *.o

