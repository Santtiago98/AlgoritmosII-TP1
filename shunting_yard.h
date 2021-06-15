#ifndef __SHUNTING_YARD_H__
#define __SHUNTING_YARD_H__

#include <iostream>
#include <string>
#include <vector>
#include "bignum.h"
#include "stack.hpp"
#include "token.hpp"


#define ADD '+' 
#define SUBSTRACT '-'
#define  MULTIPLY '*'
#define  DIVIDE '/'
            
#define LEFT_PARENTHESIS '('
#define RIGHT_PARENTHESIS ')'

#define EXCEPTION_INVALID_STACK_TO_CALCULATE 1
#define EXCEPTION_INVALID_STACK_TO_CALCULATE_MSG "La pila ingresada para calcular es invalida"

#define EXCEPTION_MISMATCH_PARENTHESES 2
#define EXCEPTION_MISMATCH_PARENTHESES_MSG "Expresion con parentesis desbalanceados"

#define EXCEPTION_UNKNOWN_PARENTHESES 3
#define EXCEPTION_UNKNOWN_PARENTHESES_MSG "No se reconoce el simbolo del parentesis"

#define EXCEPTION_UNKNOWN_TOKEN 4
#define EXCEPTION_UNKNOWN_TOKEN_MSG "No se reconoce el tipo del Token"




Stack<Token<bignum>> shunting_yard(vector<Token<bignum>> ); 
bignum calculate(Stack<Token<bignum>> *);


#endif
