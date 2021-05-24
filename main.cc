#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <string>

#include "bignum.h"
#include "cmdline.h"

using namespace std;


static void opt_input(string const &);
static void opt_output(string const &);
static void opt_precision(string const &);
//static void opt_number(string const &, int const, char * const argv[]);
static void opt_help(string const &);


/**************** Elementos globales ******************/
static option_t options[] = {
	{1, "i", "input", "-", opt_input, OPT_DEFAULT},
	{1, "o", "output", "-", opt_output, OPT_DEFAULT},
	{1, "p", "precision", PRECISION_DEFAULT_, opt_precision, OPT_DEFAULT},
	{0, "h", "help", NULL, opt_help, OPT_DEFAULT},
    //{1, "", "", OPERATION_DEFAULT, opt_number, OPT_DEFAULT},
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
	cout << "cmdline [-p precision] [-i file] [-o file]"
	     << endl;
	exit(0);
}

/*static void
opt_number(string const &arg)
{
    
    // si esta funcion se activa es que ningun argumento falló antes
    // debo chequear que se haya ingresado una operacion 
    // o que no se haya ingresado nada
    
    if (arg == OPERATION_DEFAULT)
    {
        cout << "op_number f() " << endl;
        
    }
}*/

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
    bignum result(precision);

    
    if((delimPos = str.find_first_of(operations_symbols))!= string::npos ){
    	
    	//Chequeo si hay un '-' al principio
    	if(delimPos == 0){
	    	if((delimPos = str.substr(1, str.length()).find_first_of(operations_symbols)) != string::npos ){
	    	   	delimPos += 1;
	    	}
	    	else{
	    		cerr << "Invalid Expression" <<endl;
				exit(1);
	    	}
		}
 
		//Spliteo la expresion para obtener operandos
		string s1 = str.substr(0, delimPos);
		string s2 = str.substr(delimPos+1, str.length());

		//Creo bignum desde string eliminando los espacios
		bignum op1(trim(s1),precision);
		bignum op2(trim(s2),precision);
		

		//Hago operacion detectada en el string
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
				cerr << "Invalid Operation" <<endl;
				exit(1);
		}

	}

	else{
		cerr << "Invalid Expression" <<endl;
		exit(1);
	}	

	return result;

}


void
calculate(istream *is, ostream *os)
{
	string str;

    while(getline(*iss, str)){
    	
    	//Omito linea si la expresion es vacia
    	if(str != ""){
	    	bignum result = calculate_expression(str);
	    	*oss << result << endl;    		
    	}
    }

	if (os->bad()) {
		cerr << "cannot write to output stream."
		     << endl;
		exit(1);
	}
	if (is->bad()) {
		cerr << "cannot read from input stream."
		     << endl;
		exit(1);
	}
	if (!is->eof()) {
		cerr << "cannot find EOF on input stream."
		     << endl;
		exit(1);
	}
}



int
main(int argc, char * const argv[])
{
    


	cmdline cmdl(options);	
	cmdl.parse(argc, argv);
    
    // at this point the parser should've quit the program if any argument is wrong or missing

	//Hago todos los calculos que haya en iss o me quedo esperando si es cin
	calculate(iss, oss);



    return 0;
}

