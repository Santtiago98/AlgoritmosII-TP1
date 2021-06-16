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

// Function to remove all spaces from a given string
void removeSpaces(std::string & str)
{
    // To keep track of non-space character count
    int count = 0;
 
    // Traverse the given string. If current character
    // is not space, then place it at index 'count++'
    for (size_t i = 0; i<str.length(); i++)
        if (str[i] != ' ')
            str[count++] = str[i]; 
    str.erase(count,str.length());
    
    size_t aux=0;
    while((aux=str.find_first_of('\t')) != string::npos){
        str.erase(aux, 1);
        // cout << str << endl;
        // cout << aux << endl;
    }
}





int
main(int argc, char * const argv[])
{
    
	cmdline cmdl(options);	
	cmdl.parse(argc, argv);
    
    // at this point the parser should've quit the program if any argument is wrong or missing
	//Hago todos los calculos que haya en iss o me quedo esperando si es cin
    
    bignum result, _auxres;
    //_auxres = bignum("0");
    string exp="5*(1*2)";
    
    // Strategy * multiplier = new Karatsuba_multiply;
    Strategy * multiplier = new Standard_multiply;
    
    try{
        while(1){
        //exp.clear();
        //getline(*iss, exp, '\n');
        //*oss << "\t \t INPUT: " << exp.length() << endl;
        if (!exp.length()){return 0;}
        trim(exp);
        removeSpaces(exp);
        // *oss << "\t input luego del trim : " << exp << endl;
        vector<Token<bignum>> bb; //Token<bignum> * bb=NULL;
        parseExpression(exp, bb, multiplier);
        // for(long unsigned int i=0; i < bb.size() ; i++)
        // {
            // cout << "\t token: " << bb[i] << endl;
            // // cout << "is number?  " << bb[i].isnumber() << endl;
        // }

        Stack<Token<bignum>> st_out = shunting_yard(bb);
        // while(!st_out.empty()){
            // cout << st_out.pop() << endl;
        // }
        cout << calculate(&st_out) << endl;         
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
}