#include "shunting_yard.h"

Stack<Token<bignum>> shunting_yard(std::vector<Token<bignum>> vect_tok)
{
    Stack <Token<bignum>>  operator_stack;
    Stack <Token<bignum>>   output_stack ;
    

   	Token<bignum> top_op_stack;
   	Token<bignum> token;


    size_t n = vect_tok.size();

    for(size_t i = 0; i < n ; i++)
    {
        token = vect_tok[i];
        
        if (token.isnumber()){
            output_stack.push(token);
        }

        else if (token.isoperator()){
            while ((!operator_stack.empty()) && (top_op_stack = operator_stack.top()).isoperator()   && (top_op_stack.getoperator() != LEFT_PARENTHESIS ) && (top_op_stack.getprecedence() >= token.getprecedence()))
	            {                    
                output_stack.push(operator_stack.pop());                
            }

            operator_stack.push(token);          
        }
        
        else if (token.isparenthesis()){
            if (token.getparenthesis() == LEFT_PARENTHESIS){
                operator_stack.push(token);
            }

            else if (token.getparenthesis() == RIGHT_PARENTHESIS){
                while ( (!operator_stack.empty()) && (top_op_stack = operator_stack.top()).getparenthesis() != LEFT_PARENTHESIS){                      
                    output_stack.push(operator_stack.pop());
                }
                // If the stack runs out without finding a left parenthesis, then there are mismatched parentheses. 
                if (operator_stack.empty()){
                    throw(EXCEPTION_MISMATCH_PARENTHESES);                    
                }
                // Si llego aca es parentesis (, y lo descarto
                operator_stack.pop();
            }
            else
                throw(EXCEPTION_UNKNOWN_PARENTHESES);
        }
        else    
            throw(EXCEPTION_UNKNOWN_TOKEN);
    }
    
    
    // After while loop, if operator stack not null, pop everything to output queue 
    while (!operator_stack.empty()){
        // If the operator token on the top of the stack is a parenthesis, then there are mismatched parentheses.
        if (((top_op_stack = operator_stack.top()).getparenthesis() == LEFT_PARENTHESIS) ||  (top_op_stack.getparenthesis() == RIGHT_PARENTHESIS)){
            throw(EXCEPTION_MISMATCH_PARENTHESES);
        }
        output_stack.push(operator_stack.pop());
    }

    return output_stack;
}


bignum calculate(Stack<Token<bignum>> * stack){
    
    if(!stack->empty()) {
    	Token <bignum> top_stack;
    	
        //Caso Limite: Devuelve numero
        if((top_stack = stack->top()).isnumber())
            return (stack->pop()).getdata();
        
        else if( top_stack.isoperator()){
            char op = (stack->pop()).getoperator();

            //Llamados recursivos hasta encontrar 2 numeros
            bignum b1 = calculate(stack); // poner acá el seteo
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
                    break;
            }
    	}   
    }
    throw(EXCEPTION_INVALID_STACK_TO_CALCULATE);
}