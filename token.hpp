#ifndef __TOKEN_CPP__
#define __TOKEN_CPP__

#include <iostream>
#include <string>
#include <vector>

#include "strategy.h"

#ifndef LEFT_PARENTHESIS
#define LEFT_PARENTHESIS '('
#endif

#ifndef RIGHT_PARENTHESIS
#define RIGHT_PARENTHESIS ')'
#endif

#ifndef _BIGNUM_H_INCLUDED_
#include "bignum.h"
#endif

#ifndef DEFAULT_SIZE
#define DEFAULT_SIZE  10
#endif


//using namespace std;

//enum operators {'(', ')', '{', '}', '[', ']', '*', '/', '+', '-'};

template <class T>
class Token{
    private:
        bool _isnumber, _isoperator, _isbracket, _isbinary;
        char _symbol='\0';
        unsigned int _precedence=0;
        
    public:
        T data;
        const bool isnumber() const;
        const bool isoperator() const;
        const bool isbinary() const;
        const bool isbracket() const;
        
        // CONSTRUCTORES
        Token();
        Token(std::string, Strategy *);
        Token(T); // constructor copia
        // DESTRUCTOR
        ~Token();
        // GETTERS
        T getdata() const;
        char getoperator() const;
        char getbracket() const;
        unsigned int getprecedence() const;
        
        // Asignaciones
        const Token<T> & operator=(const Token<T> &);
        
        // Lectura-Escritura 
        template <class Y>
        friend std::ostream& operator << (std::ostream&, const Token<Y>&);

};
/* ---- METODOS ---- */
template <class T>
const bool Token<T>::isnumber() const{
    return _isnumber == true? true: false;
    }

template <class T>
const bool Token<T>::isoperator() const{
    return _isoperator == true? true: false;
    }

template <class T>
const bool Token<T>::isbinary() const{
    
    return _isbinary == true? true: false;
    }
    
template <class T>
const bool Token<T>::isbracket() const{
    //std::cout << "isbracket() called " ;
    return _isbracket == true? true: false;
    }



/* ---- GETTERS ---- */
// No se deben usar sin antes verificar 
template <class T>
T Token<T>::getdata() const{// No se debe usar sin verificar que sea un number
    return data;
}

template <class T>
char Token<T>::getoperator() const{// No se debe usar sin verificar que sea un operador
    return _isoperator == true? _symbol: '\0';
}

template <class T>
char Token<T>::getbracket() const{// No se debe usar sin verificar que sea un bracket
    //std::cout << "getbracket called()" << endl;
    return this->_symbol;
}

template <class T>
unsigned int Token<T>::getprecedence() const{
    return _isoperator == true? _precedence: 0;
    }
    
/* ---- CONSTRUCTORES ---- */
template <class T>
Token<T>::Token(){
    _isnumber = true;
    _isoperator = false;
    _isbracket = false;
    _isbinary = false;
    _precedence = 0;
    _symbol = '\0';
    //data = T();
}

template <class T>
Token<T>::Token(const T token_){
    _isnumber = true;
    _isoperator = false;
    _isbracket = false;
    _isbinary = false;
    _precedence = 0;
    _symbol = '\0';
    data = token_;
}

template <class T>
Token<T>::Token(const std::string str, Strategy * str_ptr){
    
    // el string debe estar limpio
    size_t aux;
    aux = str.find_first_of("*/+-()"/*simbols.operators+simbols.parenthesis*/);
    if (aux != std::string::npos && aux +1 == str.length() ) {
        //  se encontro algun símbolo y no hay numeros
        switch(str[aux]){
            case '*':
            case '/':
                _precedence = 3;
                _isoperator = true;
                _isbinary = true;  
                _isbracket = false;                
                break;
            case '+':
            case '-':
                _precedence = 2;
                _isoperator = true;
                _isbinary = true;
                _isbracket = false;
                break;
            case '(':
            case ')':
                _precedence = 0;
                _isoperator = false;
                _isbinary = false;
                _isbracket = true;
                break;
                
        }
        _isnumber = false;
        _symbol = str[aux];
        //data = T(str);   // chequear como asignar esto para que no se fugue memoria ni se haga referencia a algo que muere
    }
    else {
        // el signo es un '+' o '-' y hay numeros
        _isoperator = false;
        _isnumber = true; 
        _isbracket = false;
        _precedence = 0;
        _isbinary = false;
        _symbol = '\0'; // plancho un \0 pues no es utilizado
        data = T(str, str_ptr); //llamo al constructor del tipo elegido
        }
}


/* ---- DETRUCTOR ---- */
template <class T>
Token<T>::~Token(){
    _isnumber = false;
    _isoperator = false;
    _isbracket = false;
    _isbinary = false;
    _precedence = 0;
    _symbol = '\0';
    //if (data != NULL) {delete [] data;}
}
/* ---- OPERADORES ---- */
template <class T>
const Token<T> & Token<T>::operator=(const Token<T> & b){
    if( this == &b ){
        return *this;
	}
    _isnumber = b._isnumber;
    _isoperator = b._isoperator;
    _isbracket = b._isbracket;
    _isbinary = b._isbinary;
    _precedence = b._precedence;
    _symbol = b._symbol;
    data = b.data;
    
    return *this;
}

// ------------------ LECTURA/ESCRITURA ------------------ //
template <class T>
std::ostream& operator << (std::ostream& os, const Token<T>& b){
	
	//os << "print bignum:" << endl;
    if (b.isnumber()){
        os << b.data ;
    }else{
        os << b._symbol ;
    }
    
    return os;
}

// ---------------------------------------------------------------------------------------
/// ---------TOKENIZE------------
/*template <class T>
class Tokens{
        
    private:
        Token<T> tokens[DEFAULT_SIZE];
        
        
    public:
        unsigned int length;
        
        // --- METODOS --- //
        Token<T> pop();
        
        // --- CONSTRUCTORES --- //
        Tokens():length(0){};
        Tokens(std::string str);

};

template <class T>
Tokens<T>::Tokens(std::string exp){
    
    if (!exp.length()) {
        std::cout << "Longitud nula" << endl;
    }
    tokens[0] = Token<T>(exp);
    std::cout << "HOLA" << endl;
}*/

// ---------------------------------------------------------------------------------------
template <class T> 
void parseExpression(const std::string exp, std::vector<T> &b, Strategy * str_ptr){
    // deja el puntero b apuntando a segmento de memoria correspondiente
    // exp es la expresion a parsear en tokens
    T fp;
    
    unsigned long int L = exp.length();
    std::string valid_characters = "*/+-()0123456789\t";//simbols_1.operators + simbols_1.digits + simbols_1.parenthesis;
    size_t aux,aux2,aux3, iter=0;
    
    // verifico que el string no presente caracteres invalidos
    // los unicos validos son los numeros y operadores y ()
    if ((aux = exp.find_first_not_of(valid_characters))!= std::string::npos){
        std::cout << "Invalid character." << std::endl;
        std::cout << exp << "<---" << std::endl;
    }
    
    if (L==0){
        std::cout << "No expression to parse. Length = 0" << std::endl;
    }
    
       
    while (iter < L){
        aux = exp.find_first_of("*/+-()"/*simbols_1.parenthesis + simbols_1.operators*/, iter);
        if (aux==std::string::npos){
            // por si los ultimos caracteres son numeros
            fp = T(exp.substr(iter, L-iter), str_ptr);
            b.push_back(fp);
            iter = L;
            break;
        }
        switch(exp[aux]){
            case '*':
            case '/':
                if (exp[aux+1] == '*' || exp[aux+1] == '/' || exp[0]=='*' || exp[0]=='/'){
                    std::cout << "Mala expresion2." << std::endl;
                    exit(1);
                    break;
                }
            case '+':
            case '-':
                if ((aux2 = exp.find_first_of("+-", aux+1)) == (aux+1)){
                    // hay dos signos + - juntos
                    // debo verificar que luego haya algun numero 
                    if((aux3 = exp.find_first_of("0123456789", aux2+1)) != aux2+1){
                        // hay 2 caracteres +,- juntos no seguidos por un numero
                        std::cout << "Mala expresion1." << std::endl;
                        exit(1);    
                        break;

                    }
                    else{//el signo aux2 debe ser parte del numero      
                        if(aux!=iter) { //por si hay nums entre iter y aux
                        fp = T(exp.substr(iter, aux-iter),str_ptr); 
                        b.push_back(fp);
                        }
                        fp = T(exp.substr(aux, 1),str_ptr); //creo el operador 
                        b.push_back(fp);
                        if ((aux3 = exp.find_first_not_of("0123456789", aux2+1)) != std::string::npos){
                        fp = T(exp.substr(aux2, aux3-aux2),str_ptr); //el numero va de aux2 a aux3
                        b.push_back(fp);
                        fp = T(exp.substr(aux3,1),str_ptr); // guardo el simbolo de aux3
                        b.push_back(fp);
                        iter = aux3+1;
                        break;
                        }
                        else{
                            fp = T(exp.substr(aux2, L-1-aux2),str_ptr); //el numero va de aux2 a L
                            b.push_back(fp);
                            iter = L;
                            break;
                        }                            
                    }  
                }
                
            default:
                // genero el token y lo agrego
                // creo el numero si corresponde, o sea aux > iter
                if(aux!=iter) {
                    fp = T(exp.substr(iter, aux-iter),str_ptr); 
                    //crear un constructor de TOKEN que reciba char para evitar el substr
                    b.push_back(fp);
                    }               
                fp = T(exp.substr(aux,1),str_ptr);
                b.push_back(fp);   
                
                iter = aux+1;
        }
  
    }
    // ahora verifco que el primer token no sea un signo de un numero
    if (b[0].isoperator()){ // el primer token no podra ser */ 
        if (b[1].isnumber()){ // debo meter el signo al numero 
            char op_ = b[0].getoperator();
            if (op_ == '+'){
                b.erase(b.begin() + 0); 
            }
            else{
                //T aux_="0";
                b[1] = T(-b[1].getdata()); //le cambio el signo y reemplazo el 1ro
                b.erase(b.begin() + 0); // elimino el signo
            }
        }
        // si no hay un numero entonces agrego un 0 al principio para que no quede desbalanceado
        // pues es un parentesis
        std::string _cero = "0";
        b.insert(b.begin(), T(_cero,str_ptr));
    }
    
    // itero todo el vector para corregir errores de parentesis 
    for (size_t j=1; j < b.size()-1; j++){ 
        if (b[j].isbracket()){
            if (b[j].getbracket() == LEFT_PARENTHESIS && b[j-1].isnumber()){
                std::cout << "Mala expresion." << std::endl;
                exit(1);
            }    
            if (b[j].getbracket() == RIGHT_PARENTHESIS && b[j+1].isnumber()){
                std::cout << "Mala expresion." << std::endl;
                exit(1);
            }
        }
        if (b[j].isoperator()){
            switch (b[j].getoperator()){
                case '*':
                case '/':
                    if (b[j-1].getbracket() == LEFT_PARENTHESIS || b[j+1].getbracket() == RIGHT_PARENTHESIS) {
                        std::cout << "Mala expresion." << std::endl;
                        exit(1);
                    } 
                    break;
                case '+':
                case '-':
                    if (b[j-1].getbracket() == LEFT_PARENTHESIS){ // parentesis u *, / 
                        if(b[j+1].isnumber()){
                            if (b[j].getoperator() == '-'){
                                b[j+1] = T(-b[j+1].getdata()); //le cambio el signo 
                                b.erase(b.begin() + j); // elimino el signo
                            } else{
                                b.erase(b.begin() +j);
                            }
                        }
                    }
                    break;
            }
        }
    }
    

}


/*
int main(){ // script para testear el funcionamiento 
    std::string exp;
    
    //Token<bignum> tok1("-69");
    //std::cout << tok1;
    
    vector<Token<bignum>> bb;
    bb.push_back(Token<bignum>("35"));
    bb.push_back(Token<bignum>("*"));
    std::cout << bb[0] << endl;
    std::cout << bb[1] << endl;
    
    
    while(true){
        cin >> exp;
        vector<Token<bignum>> bb; //Token<bignum> * bb=NULL;
        parseExpression(exp, bb);   
        for(size_t i=0; i< bb.size(); i++)
        {
        std::cout << bb[i] << endl;
        std::cout << "\t is number? " << bb[i].isnumber() << endl;
        std::cout << "\t is operator? " << bb[i].isoperator() << endl;
        std::cout << "\t precedence? " << bb[i].getprecedence() << endl;
        std::cout << "\t is bracket? " << bb[i].isbracket() << endl;
        if (bb[i].isoperator()){std::cout<<"it's an operator! --> "<< bb[i].getoperator() << endl;}
        if (bb[i].isnumber()){std::cout<<"it's a number! --> "<< bb[i].getnumber() << endl;}
        if (bb[i].isbracket()){std::cout<<"it's a bracket! --> "<< bb[i].getbracket() << endl;}
        }
        //delete [] bb;
    }
}*/

#endif
