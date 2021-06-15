
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
        // If the stack runs out without finding a left parenthesis, then there are parentheses. 
        {assert there is a left parenthesis at the top of the operator stack}
        pop the left parenthesis from the operator stack and discard it

// After the while loop, pop the remaining items from the operator stack into the output queue. 
while there are tokens on the operator stack:
    // If the operator token on the top of the stack is a parenthesis, then there are mismatched parentheses. 
    {assert the operator on top of the stack is not a (left) parenthesis}
    pop the operator from the operator stack onto the output queue

*/

#include "shunting_yard.h"


Stack<Token<bignum>> shunting_yard(vector<Token<bignum>> vect_tok)
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
        
        else if (token.isbracket()){
            if (token.getbracket() == LEFT_PARENTHESIS){
                operator_stack.push(token);
            }

            else if (token.getbracket() == RIGHT_PARENTHESIS){
                while ( (!operator_stack.empty()) && (top_op_stack = operator_stack.top()).getbracket() != LEFT_PARENTHESIS){                      
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
        if (((top_op_stack = operator_stack.top()).getbracket() == LEFT_PARENTHESIS) ||  (top_op_stack.getbracket() == RIGHT_PARENTHESIS)){
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
                    //return b2 / b1;
                    break;
            }
    	}   
    }
    throw(EXCEPTION_INVALID_STACK_TO_CALCULATE);
}

/*
int main()
{

    string exp;

    try{
        while(1){
        cin >> exp;
        vector<Token<bignum>> bb; //Token<bignum> * bb=NULL;
        parseExpression(exp, bb);
        for(long unsigned int i=0; i < bb.size() ; i++)
            cout << "token:" << bb[i] <<"-" ;

        Stack<Token<bignum>>  st_out = shunting_yard(bb);
        cout << endl << calculate(&st_out) <<endl ;        
        }
        
    }
    catch(int exc){
        switch(exc){
            case EXCEPTION_INVALID_STACK_TO_CALCULATE:
                cerr <<  EXCEPTION_INVALID_STACK_TO_CALCULATE_MSG << endl;
                break;
            case EXCEPTION_MISMATCH_PARENTHESES:
                cerr <<  EXCEPTION_MISMATCH_PARENTHESES_MSG << endl;
               break;
            case EXCEPTION_UNKNOWN_TOKEN:
                cerr <<  EXCEPTION_UNKNOWN_TOKEN_MSG << endl;
               break;
            case EXCEPTION_UNKNOWN_PARENTHESES:
                cerr <<  EXCEPTION_UNKNOWN_PARENTHESES_MSG << endl;
               break;
            
        }
    }    

    

	return 0;
}*/