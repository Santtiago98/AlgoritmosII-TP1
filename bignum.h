#ifndef _BIGNUM_H_INCLUDED_
#define _BIGNUM_H_INCLUDED_

#include <iostream>
#include <string>
#include <algorithm>
#include <math.h> 
#include "./bignum.h"

#ifndef BIGNUM_PRECISION_DEFAULT
#define BIGNUM_PRECISION_DEFAULT 10
#endif

#ifndef BIGNUM_PRECISION_INT
#define BIGNUM_PRECISION_INT 10
#endif

#ifndef BIGNUM_MSG_ERR_PRECISION
#define BIGNUM_MSG_ERR_PRECISION "PRECISION IS NOT ENOUGH"
#endif

#ifndef BIGNUM_MSG_ERR_INVALID_CHARS
#define BIGNUM_MSG_ERR_INVALID_CHARS "THE INPUT CHARS SHOULD BE DIGITS"
#endif

using namespace std;

class bignum{
	
    private:
	
	// --- ATRIBUTOS --- //
        unsigned short *digits;
        unsigned short precision;
		unsigned short effective_size;
        bool negative;

	// --- METODOS PRIVADOS USADOS INTERNAMENTE --- //
		friend unsigned short max_precision(const bignum& , const bignum& ); // determina la maxima precision entre dos bignums
		friend unsigned short min_precision(const bignum& , const bignum& ); // determina la minima precision entre dos bignums
		friend unsigned short max_size(const bignum& , const bignum& ); //determina el maximo effective_size entre dos bignums
		friend unsigned short min_size(const bignum& , const bignum& ); //determina el minimo effective_size entre dos bignums
		friend unsigned short size( bignum const & ); //determina el effective_size en un bignum

    public:

	// --- METODOS PARA DEVOLVER ATRIBUTOS --- //
		unsigned short prec(void) const;
		unsigned short eff_size(void) const;
		bool is_negative() const;
		bool sign() const ;
	
	// --- DESTRUCTOR --- //
		~bignum();
		
	// --- CONSTRUCTORES --- //
		bignum(); //prec x defecto - Inicializado en 0
		bignum(const unsigned short p); //bignum con cierta precision
		bignum(const int n, const unsigned short p); //bignum a partir de un int y una precision dada
		bignum(const std::string &, const unsigned short p);   //bignum a partir de un string
		bignum(const char* c_arr, const unsigned short p); //bignum a partir de un arreglo de chars
		bignum(const bignum &);  //constructor copia
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
		friend const bignum operator*(const bignum&, const bignum&);  //p =pmax{p1,p2}
	
	// --- ASIGNACIONES --- //
		const bignum & operator=(const bignum &b);
		const bignum & operator=(const int &n);
		
	// --- COMPARADORES --- //
		friend bool operator<(bignum const &b1, bignum const &b2); // b1 < b2
		friend bool operator>(bignum const &b1, bignum const &b2); // b1 > b2
		friend bool operator==(bignum const &b1, bignum const &b2); // b1 == b2
		friend bool operator<=(bignum const &b1, bignum const &b2); // b1 <= b2
		friend bool operator>=(bignum const &b1, bignum const &b2); // b1 >= b2
	
	// --- LECTURA/ESCRITURA --- //
		friend std::ostream& operator<<(std::ostream&, const bignum&);
		friend std::istream& operator>>(std::istream&, bignum&);
		
		
};

#endif