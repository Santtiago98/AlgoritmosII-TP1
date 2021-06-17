#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <string>
#include <vector>

#include "cmdline.h"
// #include "strategy.h"
#include "bignum.h"
#include "token.hpp"
#include "stack.hpp"
#include "shunting_yard.h"
#include "karatsuba.h"
#include "standard_multiply.h"

using namespace std;

#define	STANDARD_MULTIPLIER "standard"
#define	KARATSUBA_MULTIPLIER "karatsuba"


// struct Symbols {
    // string operators = "*/+-";
    // string parenthesis = "()";
    // int precedence[4] = {3,3,2,2};
    // string digits = "0123456789";
// } simbols;

static void opt_input(string const &);
static void opt_output(string const &);
static void opt_multiplier(string const &);
static void opt_help(string const &);


/**************** Elementos globales ******************/
static option_t options[] = {
	{1, "i", "input", "-", opt_input, OPT_DEFAULT},
	{1, "o", "output", "-", opt_output, OPT_DEFAULT},
	{1, "m", "multiplier", KARATSUBA_MULTIPLIER , opt_multiplier, OPT_DEFAULT},
	{0, "h", "help", NULL, opt_help, OPT_DEFAULT},
	{0, },
};

//static int precision;
static istream *iss = 0;	// Input Stream (clase para manejo de los flujos de entrada)
static ostream *oss = 0;	// Output Stream (clase para manejo de los flujos de salida)
static fstream ifs; 		// Input File Stream (derivada de la clase ifstream que deriva de istream para el manejo de archivos)
static fstream ofs;		// Output File Stream (derivada de la clase ofstream que deriva de ostream para el manejo de archivos)

static Strategy * mult_algorithm = 0;


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
opt_multiplier(string const &arg)
{
	if(arg == STANDARD_MULTIPLIER){
		mult_algorithm = new Standard_multiply;
	}
	else if(arg == KARATSUBA_MULTIPLIER ){
		mult_algorithm = new Karatsuba_multiply;
	}
	else{
		cerr << "Invalid Mulplier argument " << endl;
		exit(1);
	}

}


static void
opt_help(string const &arg)
{	
	cout << "FIUBA - 95.12 Algoritmos y Programación II - 2021 C1 - Grupo C - Anus, Aupi, Boudjikanian - TP1"
		 << endl
	     << endl;
	cout << "Program help"
	     << endl;
	cout << "cmdline options: "
		 << endl
		 << "[-m --multiplier] define the algorithm to multiply, (options are 'karatsuba' and 'standard'), default is " << KARATSUBA_MULTIPLIER
		 << endl
		 << "[-i --input ] define input file, by default stdin"
		 << endl
		 << "[-o --output] define output file, by default stdout"
	     << endl
		 << "[-h --help] prints a basic help (this) and exits"
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

// Function to remove all spaces from a given string
void removeSpaces(std::string & str)
{
    // To keep track of non-space character count
    int count = 0;
 
    // Reverse the given string. If current character
    // is not space, then place it at index 'count++'
    for (size_t i = 0; i<str.length(); i++)
        if (str[i] != ' ')
            str[count++] = str[i]; 
    str.erase(count,str.length());
    
    size_t aux=0;
    while((aux=str.find_first_of('\t')) != string::npos){
        str.erase(aux, 1);
    }
    
}


int
main(int argc, char * const argv[])
{
    
	cmdline cmdl(options);	
	cmdl.parse(argc, argv);

    // at this point the parser should've quit the program if any argument is wrong or missing
   
    string exp="12*34";

    try{
        while(getline(*iss, exp, '\n')){

            if (!exp.length()){continue;}
            trim(exp);
            removeSpaces(exp);
            
            vector<Token<bignum>> tokens; 
            parseExpression(exp, tokens, mult_algorithm);
            
            Stack<Token<bignum>> st_out = shunting_yard(tokens);
            *oss << calculate(&st_out) << endl;         
            }
        delete  mult_algorithm; 
    }
    
    
    catch(int exc){
        delete  mult_algorithm; 
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
            case WRONG_EXPRESION_MISSING_OPERAND_BEFORE_PARENTHESIS:
                cerr << WRONG_EXPRESION_MISSING_OPERAND_BEFORE_PARENTHESIS_MSG <<endl;
                break;
            case WRONG_EXPRESION_MISSING_OPERAND_AFTER_PARENTHESIS:
                cerr << WRONG_EXPRESION_MISSING_OPERAND_AFTER_PARENTHESIS_MSG <<endl;
                break;
            case CONSECUTIVES_OPERATORS_MULTIPLY_DIVIDE:
                cerr << CONSECUTIVES_OPERATORS_MULTIPLY_DIVIDE_MSG << endl;
                break;
            case CONSECUTIVES_OPERATORS_SUM_MINUS_WITHOUT_NUMBER:
                cerr << CONSECUTIVES_OPERATORS_SUM_MINUS_WITHOUT_NUMBER_MSG << endl;
                break;
            case WRONG_MULTIPLY_DIVIDE_PARENTHESIS_COMBINATION:
                cerr << WRONG_MULTIPLY_DIVIDE_PARENTHESIS_COMBINATION_MSG << endl;
                break;
            case NO_INPUT_EXPRESSION:
                cerr << NO_INPUT_EXPRESSION_MSG << endl;
                break;
        }   
    } 



    return 0;
}