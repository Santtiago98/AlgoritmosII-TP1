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

TP1 = ./tp1 # -m standard
# TP1 = bc
# TP1 = valgrind --tool=memcheck --error-exitcode=1 tp1

test tests: 0-warmup.out 1-spaces.out 2-precision.out 3-recursion.out 4-mixed.out
	@echo OK

clean_test:
	rm -f *.out || :

0-warmup.out: 0-warmup.in
	@$(TP1) < 0-warmup.in > 0-warmup.out
	@diff -s -b 0-warmup.out 0-warmup.ref

1-spaces.out: 1-spaces.in
	@$(TP1) < 1-spaces.in > 1-spaces.out
	@diff -s -b 1-spaces.out 1-spaces.ref

2-precision.out: 2-precision.in
	@$(TP1) < 2-precision.in > 2-precision.out
	@diff -s -b 2-precision.out 2-precision.ref

3-recursion.out: 3-recursion.in
	@$(TP1) < 3-recursion.in > 3-recursion.out
	@diff -s -b 3-recursion.out 3-recursion.ref

4-mixed.out: 4-mixed.in
	@$(TP1) < 4-mixed.in > 4-mixed.out
	@diff -s -b 4-mixed.out 4-mixed.ref
