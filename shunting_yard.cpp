
// This implementation does not implement composite functions, functions with variable number of arguments, and unary operators. 
/*
while there are tokens to be read:
    read a token
    if the token is:
    - a number:
        put it into the output queue

    - an operator o1:
        while (there is an operator o2 other than the left parenthesis
              at the top of the operator stack, and either o1 is left-associative and its precedence is less or equal to that of o2, or o1 is right-associative and its precedence is less than o2):
            pop o2 from the operator stack into the output queue
        push o1 onto the operator stack

    - a left parenthesis (i.e. "("):
        push it onto the operator stack

    - a right parenthesis (i.e. ")"):
        while the operator at the top of the operator stack is not a left parenthesis:
            pop the operator from the operator stack into the output queue
        // If the stack runs out without finding a left parenthesis, then there are mismatched parentheses. 
        {assert there is a left parenthesis at the top of the operator stack}
        pop the left parenthesis from the operator stack and discard it

// After the while loop, pop the remaining items from the operator stack into the output queue. 
while there are tokens on the operator stack:
    // If the operator token on the top of the stack is a parenthesis, then there are mismatched parentheses. 
    {assert the operator on top of the stack is not a (left) parenthesis}
    pop the operator from the operator stack onto the output queue

*/
#include <iostream>
#include <string>
#include <vector>
#include "bignum.h"
//#include "bignum.cc"
#include "stack.hpp"
#include "token.cpp"


#define ADD '+' 
#define SUBSTRACT '-'
#define  MULTIPLY '*'
#define  DIVIDE '/'
            


Stack<Token<bignum>> shunting_yard(vector<Token<bignum>> vect_tok)
{
    Stack <Token<bignum>>  operator_stack;
    Stack <Token<bignum>>   output_stack ;
    

   	Token<bignum> top_op_stack;
   	Token<bignum> token;


    int n = vect_tok.size();

    for(int i = 0; i < n ; i++)
    {
        token = vect_tok[i];
        
    
        if (token.isnumber()){
            output_stack.push(token);
        }
      

        else if (token.isoperator()){
            while ((!operator_stack.empty()) && (top_op_stack = operator_stack.top()).isoperator()   && (top_op_stack.getoperator() != '(' ) && (top_op_stack.getprecedence() >= token.getprecedence()))
	            {                    
                output_stack.push(operator_stack.pop());                
            }

            operator_stack.push(token);          
        }
    
        
        else if (token.getoperator() == '('){
            operator_stack.push(token);
        }


        else if (token.getoperator() == ')'){
            while ( (!operator_stack.empty()) && (top_op_stack = operator_stack.top()).getoperator() == '('){                      
                output_stack.push(operator_stack.pop());
            }
            // If the stack runs out without finding a left parenthesis, then there are mismatched parentheses. 
            if (operator_stack.empty()){
                
                cerr << "desbalanceada" << endl;//error - expresion desbalanceada
                exit(1);
                //salir
            }
            // Si llego aca es parentesis (, y lo descarto
            operator_stack.pop();
        }
    }
    
    
    // After while loop, if operator stack not null, pop everything to output queue 
    while (!operator_stack.empty()){
        // If the operator token on the top of the stack is a parenthesis, then there are mismatched parentheses.
        if (((top_op_stack = operator_stack.top()).getoperator() == '(') ||  (top_op_stack.getoperator() == ')')){
                cerr << "desbalanceada2" << endl;//error - expresion desbalanceada
                exit(1);
            //salir
        }
        output_stack.push(operator_stack.pop());
    }
    

    return output_stack;
}


bignum calculate(Stack<Token<bignum>> * stack){

    if(!stack->empty()) {
    	Token <bignum> top_op_stack;
    	

        if((top_op_stack = stack->top()).isnumber())
            return (stack->pop()).getdata();
        

        else if( top_op_stack.isoperator()){
            char op = (stack->pop()).getoperator();

            bignum b1 = calculate(stack);
            bignum b2 = calculate(stack);

            switch(op){
                case ADD:
                    return b1 + b2;
                case SUBSTRACT:
                    return b2 - b1;
                case MULTIPLY:
                    return b1 * b2;
                case DIVIDE:
                    return b2 / b1;
            }
    	}
    }
        

    
    cerr << "pila desbalanceada no se puede calcular" << endl;
    exit(1);         // empty - ver que hago
    
    

}


int main()
{


    string exp;

    while(true){

    cin >> exp;
    vector<Token<bignum>> bb; //Token<bignum> * bb=NULL;
    parseExpression(exp, bb);   
    Stack<Token<bignum>>  st_out = shunting_yard(bb);
    cout << calculate(&st_out) <<endl ;

    }

	return 0;
}