#ifndef _BIGNUM_H_INCLUDED_
#define _BIGNUM_H_INCLUDED_


#include <iostream>
#include <string>
#include <algorithm>
#include <math.h>
#include <exception>
#include <stdlib.h>
#include <map>
#include <utility>
#include <vector>
// #include "strategy.h"

#ifndef BIGNUM_PRECISION_DEFAULT
#define BIGNUM_PRECISION_DEFAULT 10
#endif

#ifndef BIGNUM_PRECISION_INT
#define BIGNUM_PRECISION_INT 20
#endif

#ifndef BIGNUM_MSG_ERR_PRECISION
#define BIGNUM_MSG_ERR_PRECISION "PRECISION IS NOT ENOUGH"
#endif

#ifndef BIGNUM_MSG_ERR_INVALID_CHARS
#define BIGNUM_MSG_ERR_INVALID_CHARS "THE INPUT CHARS SHOULD BE DIGITS"
#endif

#ifndef BIGNUM_MSG_ERR_BAD
#define BIGNUM_MSG_ERR_BAD "NaN"
#endif


class Strategy;
class bignum{
    
	
    private:
	
	// --- ATRIBUTOS --- //
        unsigned short *digits;
		unsigned long bn_length;
        bool negative;
        Strategy * strategy_ptr;
        friend class Strategy;
        friend class Standard_multiply;
        friend class Karatsuba_multiply;
	// --- METODOS PRIVADOS USADOS INTERNAMENTE --- //
		friend unsigned long max_size(const bignum& , const bignum& ); //determina el maximo effective_size entre dos bignums
		friend unsigned long min_size(const bignum& , const bignum& ); //determina el minimo effective_size entre dos bignums
		friend const bignum bn_exp_10(unsigned long expo); //crea un bignum que representa 10^exp
		friend const bignum bn_mult_pow10_(const bignum& , unsigned long n);
		

    public:
        
		bool bad() const;
	
	// --- DESTRUCTOR --- //
		~bignum();
		
	// --- CONSTRUCTORES --- //
		bignum(); //prec x defecto - Inicializado en 0
		bignum(const int n,  Strategy *a=NULL); //bignum a partir de un int y una precision dada
		bignum(const std::string &, Strategy*a=NULL);   //bignum a partir de un string
		bignum(const char* c_arr,  Strategy*a  =NULL); //bignum a partir de un arreglo de chars
		bignum(const bignum &);  //constructor copia
        //bignum(const Strategy*); // constructor c/ Strategy
		bignum const operator+=(const bignum &);
		bignum const operator-=(const bignum &);
		bignum const operator*=(const bignum &);
		bignum const operator+=(const int);
		bignum const operator-=(const int);
		bignum const operator*=(const int);

	// --- OPERACIONES ALGEBRAICAS --- //
		friend const bignum operator+(const bignum&, const bignum&);  // b1 + b2
		friend const bignum operator-(const bignum& b1, const bignum& b2); // b1 - b2
		friend const bignum operator-(const bignum& b1); // -b1
		friend const bignum operator*(const bignum& b1, const bignum& b2); // b1*b2
		friend const bignum operator/(const bignum& b1, const bignum& b2); // b1/b2

		
	// --- ASIGNACIONES --- //
		const bignum & operator=(const bignum &b);
		const bignum & operator=(const int n);
		
	// --- COMPARADORES --- //
		friend bool operator<(bignum const &b1, bignum const &b2); // b1 < b2
		friend bool operator>(bignum const &b1, bignum const &b2); // b1 > b2
		friend bool operator==(bignum const &b1, bignum const &b2); // b1 == b2
		friend bool operator<=(bignum const &b1, bignum const &b2); // b1 <= b2
		friend bool operator>=(bignum const &b1, bignum const &b2); // b1 >= b2
	
	// --- LECTURA/ESCRITURA --- //
		friend std::ostream& operator<<(std::ostream&, const bignum&);
		friend std::istream& operator>>(std::istream&, bignum&);
		
    // --- SETERS --- //
        void set_strategy(Strategy *);
};



#endif