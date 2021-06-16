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
#define EXCEPTION_INVALID_STACK_TO_CALCULATE_MSG "Input stack is invalid"

#define EXCEPTION_MISMATCH_PARENTHESES 2
#define EXCEPTION_MISMATCH_PARENTHESES_MSG "Unbalanced expression"

#define EXCEPTION_UNKNOWN_PARENTHESES 3
#define EXCEPTION_UNKNOWN_PARENTHESES_MSG "The parenthesis symbol is not recognized, neither '(' nor ')'"

#define EXCEPTION_UNKNOWN_TOKEN 4
#define EXCEPTION_UNKNOWN_TOKEN_MSG "Token is not recognized"




Stack<Token<bignum>> shunting_yard(std::vector<Token<bignum>> ); 
bignum calculate(Stack<Token<bignum>> *);


#endif
