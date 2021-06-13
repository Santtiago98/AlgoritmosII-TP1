#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <string>
#include <vector>


#include "cmdline.h"

#ifndef _BIGNUM_H_INCLUDED_
#include "bignum.h"
#endif


#ifndef __TOKEN_CPP__
#include "token.cpp"
#endif

#ifndef __STACK_H__
#include "stack.hpp"
#endif


using namespace std;

struct Symbols {
    string operators = "*/+-";
    string parenthesis = "()";
    int precedence[4] = {3,3,2,2};
    string digits = "0123456789";
} simbols;

static void opt_input(string const &);
static void opt_output(string const &);
static void opt_precision(string const &);
static void opt_help(string const &);


/**************** Elementos globales ******************/
static option_t options[] = {
	{1, "i", "input", "-", opt_input, OPT_DEFAULT},
	{1, "o", "output", "-", opt_output, OPT_DEFAULT},
	{1, "p", "precision", PRECISION_DEFAULT_, opt_precision, OPT_DEFAULT},
	{0, "h", "help", NULL, opt_help, OPT_DEFAULT},
	{0, },
};

static int precision;
static istream *iss = 0;	// Input Stream (clase para manejo de los flujos de entrada)
static ostream *oss = 0;	// Output Stream (clase para manejo de los flujos de salida)
static fstream ifs; 		// Input File Stream (derivada de la clase ifstream que deriva de istream para el manejo de archivos)
static fstream ofs;		// Output File Stream (derivada de la clase ofstream que deriva de ostream para el manejo de archivos)


/*****************************************************/
static void
opt_input(string const &arg)
{
	// Si el nombre del archivos es "-", usaremos la entrada
	// estándar. De lo contrario, abrimos un archivo en modo
	// de lectura.

	if (arg == "-") {
		iss = &cin;		// Establezco la entrada estandar cin como flujo de entrada
	}
	else {
		ifs.open(arg.c_str(), ios::in); // c_str(): Returns a pointer to an array that contains a null-terminated
										// sequence of characters (i.e., a C-string) representing
										// the current value of the string object.
		iss = &ifs;
	}

	// Verificamos que el stream este OK.

	if (!iss->good()) {
		cerr << "cannot open "
		     << arg
		     << "."
		     << endl;
		exit(1);
	}
}

static void
opt_output(string const &arg)
{
	// Si el nombre del archivos es "-", usaremos la salida
	// estándar. De lo contrario, abrimos un archivo en modo
	// de escritura.

	if (arg == "-") {
		oss = &cout;	// Establezco la salida estandar cout como flujo de salida
	} else {
		ofs.open(arg.c_str(), ios::out);
		oss = &ofs;
	}

	// Verificamos que el stream este OK.

	if (!oss->good()) {
		cerr << "cannot open "
		     << arg
		     << "."
		     << endl;
		exit(1);		// EXIT: Terminación del programa en su totalidad
	}
}

static void
opt_precision(string const &arg)
{
	istringstream iss(arg);

	// Intentamos extraer el factor de la línea de comandos.
	// Para detectar argumentos que únicamente consistan de
	// números enteros, vamos a verificar que EOF llegue justo
	// después de la lectura exitosa del escalar.

	if (!(iss >> precision) || !iss.eof()) {
		cerr << "non-integer precision: "
		     << arg
		     << "."
		     << endl;
		exit(1);
	}
    
    if (precision <= 0){
        cerr << "non-positive precision: "
            << arg
            << "."
            << endl;
        exit(1);
    }
    
	if (iss.bad()) {
		cerr << "cannot read integer precision."
		     << endl;
		exit(1);
	}
}

static void
opt_help(string const &arg)
{	
	cout << "FIUBA - 95.12 Algoritmos y Programación II - 2021 C1 - Grupo C - Anus, Aupi, Boudjikanian - TP0"
		 << endl
	     << endl;
	cout << "Program help"
	     << endl;
	cout << "cmdline options: "
		 << endl
		 << "[-p precision] define precision used by program (number of digits use to represent the number), default is " << BIGNUM_PRECISION_DEFAULT 
		 << endl
		 << "[-i file] define input file, by default stdin"
		 << endl
		 << "[-o file] define output file, by default stdout"
	     << endl
		 << "[-h] prints a basic help"
	     << endl;
	cout << endl
	     << "Developed by marto-chiqui-panter"
		 << endl;
	exit(0);
}


std::string& ltrim(std::string& str, const std::string& chars = "\t\n\v\f\r ")
{
    str.erase(0, str.find_first_not_of(chars));
    return str;
}
 
std::string& rtrim(std::string& str, const std::string& chars = "\t\n\v\f\r ")
{
    str.erase(str.find_last_not_of(chars) + 1);
    return str;
}
 
std::string& trim(std::string& str, const std::string& chars = "\t\n\v\f\r ")
{
    return ltrim(rtrim(str, chars), chars);
}


const bignum calculate_expression(const string & str){

    string operations_symbols = "+-*";
    size_t delimPos;
    size_t aux=0;
    bignum result(precision);

    
    if((delimPos = str.find_first_of(operations_symbols))!= string::npos ){
        //cout << "str: " << str << endl;
    	//cout << "delim: " << delimPos << endl;
        
    	// Chequeo si hay un '+/-' al principio
    	if(delimPos == 0){
	    	if((delimPos = str.find_first_of(operations_symbols,1)) == string::npos ){
                // no se encontró otro operador 
	    		cerr << "Invalid expression." <<endl;
				exit(1);
	    	}
		}
 
		// Spliteo la expresion para obtener operandos
		string s1 = str.substr(0, delimPos);
		string s2 = str.substr(delimPos+1, str.length());
        
        // Elimino los espacioes y caracteres espurios
        s1 = trim(s1);
        s2 = trim(s2);
        
        if (s1.length() == 0 || s2.length() == 0){
            cout << "Missing operand." << endl;
            exit(1);
        }
        else if(((aux = s2.find_first_of(operations_symbols,1)) != string::npos)){
            // se encontró otro operador luego del primer caracter inicial
            cout << "Invalid operand." << endl;
            exit(1);
        }
        else if ((aux = s2.find_first_of(operations_symbols)) == s2.length()-1){
            cout << "Invalid operand." << endl;
            exit(1);           
            
        }
        else if(((aux = s1.find_first_of(operations_symbols,1)) != string::npos)){
            // se encontró otro operador luego del primer caracter inicial
            cout << "Invalid operand." << endl;
            exit(1);
        }
        else if ((aux = s1.find_first_of(operations_symbols)) == s1.length()-1){
            cout << "Invalid operand." << endl;
            exit(1);           
            
        }
        
        
        
		// Creo bignum desde string
		bignum op1(s1,precision);
		bignum op2(s2,precision);
        
		if (op1.bad() || op2.bad()){                        
            cout << "Invalid expresion." << endl;
            exit(1);
        }
        

		// Hago operacion detectada en el string
		switch(str[delimPos]){
			case '+':
				result = op1 + op2;
				break;
			case '-':
				result = op1 - op2;
				break;
			case '*':
				result = op1 * op2;
				break;
			default:
				cerr << "Invalid operation." <<endl;
				exit(1);
		}
	}

	else{
		cerr << "Invalid Expression" <<endl;
		exit(1);
	}	

    if (result.bad()){                        
        cout << "Out of precision." << endl;
        exit(1);
    }
	return result;

}



#define ADD '+' 
#define SUBSTRACT '-'
#define MULTIPLY '*'
#define DIVIDE '/'
 


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
                //case DIVIDE:
                  //  return b2 / b1;
            }
    	}
    }
        

    
    cerr << "pila desbalanceada no se puede calcular" << endl;
    exit(1);         // empty - ver que hago
    
    

}


int
main(int argc, char * const argv[])
{
    


	cmdline cmdl(options);	
	cmdl.parse(argc, argv);
    
    // at this point the parser should've quit the program if any argument is wrong or missing
	//Hago todos los calculos que haya en iss o me quedo esperando si es cin
    string exp;

    while(true){
        cin >> exp;
        vector<Token<bignum>> bb; //Token<bignum> * bb=NULL;
        parseExpression(exp, bb);   
        for(size_t i=0; i< bb.size(); i++)
        {
            cout << bb[i] << endl;
            cout << "\t is number? " << bb[i].isnumber() << endl;
            cout << "\t is operator? " << bb[i].isoperator() << endl;
            //cout << "\t is binary? " << bb[i].isbinary() << endl;
            cout << "\t is bracket? " << bb[i].isbracket() << endl;
            //if (bb[i].isoperator()){cout<<"it's an operator! --> "<< bb[i].getoperator() << endl;}
            if (bb[i].isnumber()){cout<<"it's a number! --> "<< bb[i].getdata() << endl;}
        }
        cout << " ------ NOW OPERATE ------ " << endl;
        Stack<Token<bignum>>  st_out = shunting_yard(bb);
        cout << calculate(&st_out) <<endl ;
    }
        
	if (oss->bad()) {
		cerr << "cannot write to output stream."
		     << endl;
		exit(1);
	}
	if (iss->bad()) {
		cerr << "cannot read from input stream."
		     << endl;
		exit(1);
	}
	if (!iss->eof()) {
		cerr << "cannot find EOF on input stream."
		     << endl;
		exit(1);
	}



    return 0;
}