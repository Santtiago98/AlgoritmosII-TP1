#ifndef _TOKEN_H_INCLUDED_
#define _TOKEN_H_INCLUDED_

#include <iostream>
#include <string>
#include "bignum.h"

#ifndef DEFAULT_SIZE
#define DEFAULT_SIZE  10
#endif

#ifndef INIT_SIZE
#define INIT_SIZE 25
#endif

using namespace std;

//enum operators {'(', ')', '{', '}', '[', ']', '*', '/', '+', '-'};

struct Symbols {
    string operators = "*/+-";
    string parenthesis = "()[]{}";
    int precedence[4] = {3,3,2,2};
    string digits = "0123456789";
} simbols;

template <class T>
class Token{
    private:
        bool _number, _operator, _binary;
        unsigned int _precedence;
        T data;
        
    public:
        const bool isnumber();
        const bool isoperator();
        const bool isbinary();
        Token();
        Token(string);
        
        // Asignaciones
        const Token<T> & operator=(const Token<T> &);

};
/* ---- METODOS ---- */
template <class T>
const bool Token<T>::isnumber(){
    return _number == true? true: false;
    }

template <class T>
const bool Token<T>::isoperator(){
    return _operator == true? true: false;
    }

template <class T>
const bool Token<T>::isbinary(){
    return _binary == true? true: false;
    }

/* ---- CONSTRUCTORES ---- */
template <class T>
Token<T>::Token(){
    _number = false;
    _operator = false;
    _binary = false;
    _precedence = 0;
    //data = NULL;
}

/* ---- OPERADORES ---- */
template <class T>
const Token<T> & Token<T>::operator=(const Token<T> & b){
    if( this == &b ){
        return *this;
	}
    _number = b._number;
    _operator = b._operator;
    _binary = b._binary;
    _precedence = b._precedence;
    data = b.data;
    
    return *this;
}

template <class T>
Token<T>::Token(const string str){
    
    // el string debe estar limpio
    int aux;
    aux = str.find_first_of(simbols.operators);
    if (aux != string::npos && aux == str.length() -1 ) {
        //  se encontro algun símbolo y no hay numeros
        switch(str[aux]){
            case '*':
            case '/':
                _precedence = 3;
                break;
            case '+':
            case '-':
                _precedence = 2;
                break;
        }
        _operator = true;
        _binary = true;
        _number = false;
        //data = sign;   // chequear como asignar esto para que no se fugue memoria ni se haga referencia a algo que muere
    }
    else if (aux != string::npos){
        // el signo es un '+' o '-' y hay numeros
        _operator = false;
        _number = true; 
        _precedence = 2;
        _binary = false;
        
        data = T(str); //llamo al constructor del tipo elegido
        }
}

// ---------------------------------------------------------------------------------------
/// ---------TOKENIZE------------
template <class T>
class Tokens{
        
    private:
        Token<T> tokens[DEFAULT_SIZE];
        
        
    public:
        unsigned int length;
        
        // --- METODOS --- //
        Token<T> pop();
        
        // --- CONSTRUCTORES --- //
        Tokens():length(0){};
        Tokens(string str);

};

template <class T>
Tokens<T>::Tokens(string exp){
    
    if (!exp.length()) {
        cout << "Longitud nula" << endl;
    }
    tokens[0] = Token<T>(exp);
    cout << "HOLA" << endl;
}

// ---------------------------------------------------------------------------------------
template <class T> 
void parseExpression(string const exp, Token<T> * b){
    // deja el puntero b apuntando a segmento de memoria correspondiente
    // exp es la expresion a parsear en tokens
    
    unsigned long int L = exp.length();
    unsigned long int alloc_size = 0, used_size=0;
    Symbols simbols_1; //esta estructura contiene los simbolos soportados
    string valid_characters = simbols_1.operators + simbols_1.digits + simbols_1.parenthesis;
    size_t aux,aux2, iter=0;
    
    // verifico que el string no presente caracteres invalidos
    // los unicos validos son los numeros y operadores y ()[]{}
    if ((aux = exp.find_first_not_of(valid_characters))!= string::npos){
        cout << "Invalid character." << endl;
        cout << exp << endl;
    }
    
    if (L==0){
        cout << "No expression to parse. Length = 0" << endl;
    }
    
    if ((b = new Token<T>[INIT_SIZE]) == NULL){
        cout << "Can't initialice memory." << endl;
        exit(1);
    } 
    alloc_size = INIT_SIZE;
       
    while (iter < L){
        aux = exp.find_first_of(simbols_1.parenthesis + simbols_1.operators, iter);
        if (aux==string::npos){
            // por si los ultimos caracteres son numeros
            b[used_size++] = new Token<T> (exp.substr(iter, L-iter));
            iter = L;
            break;
        }
        switch(exp[aux]){
            case '+':
            case '-':
                if ((aux2 = exp.find_first_of("+-", aux+1)) == (aux+1)){
                    // hay dos signos + - juntos
                    // debo verificar que luego haya algun numero o parentesis
                    if(exp[aux+2] == '+' || exp[aux+2] == '-'){
                        // hay 3 o mas caracteres + - juntos 
                        cout << "Mala expresion." << endl;
                        exit(1);    
                        break;
                    }
                    else{//el signo debe ser parte del numero                 
                    }  
                }
            case '*':
            case '/':
                if (exp[aux+1] == '*' || exp[aux+1] == '/'){
                    cout << "Mala expresion." << endl;
                    exit(1); 
                }
            default:
                // genero el token y lo agrego
                // previamente chequeo que no este lleno el array
                if (used_size == alloc_size){
                    //copiar todo a otro array
                }
                b[used_size++] = new Token<T> (exp.substr(iter, aux-iter));
                b[used_size++] = new Token<T> (exp[aux]);
                iter = aux+1;   
        }
    }
}



int main(){
    string exp="1+3*54";
    
    cout << "Operación a realizar" << endl;
    //cin >> exp;
    cout << "Expresion ingresada: " << exp << endl;
    
    Token<bignum> *bb;
    parseExpression(exp, bb);
    
    delete [] bb;
    
}

#endif
