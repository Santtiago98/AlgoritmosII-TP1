#ifndef _BIGNUM_H_INCLUDED_
#define _BIGNUM_H_INCLUDED_

#include <iostream>
#include <string>
#include <algorithm>
#include <math.h> 
#include "./bignum.h"

#ifndef PRECISION_DEFAULT
#define PRECISION_DEFAULT 10
#endif

#ifndef PRECISION_INT
#define PRECISION_INT 10
#endif

using namespace std;

class bignum{
	
    private:
        unsigned short *digits;
        unsigned short precision; // prec=4 --> XXXX
		unsigned short effective_size;
        bool negative;
    // ...
		friend unsigned short max_precision(const bignum& , const bignum& );
		friend unsigned short min_precision(const bignum& , const bignum& );
		friend unsigned short max_size(const bignum& , const bignum& );
		friend unsigned short min_size(const bignum& , const bignum& );
		friend unsigned short size( bignum const & );
		// friend unsigned short prec_(void) const;
		// friend unsigned short effsize(void) const;
		// friend bool sign(void) const;
    public:
    // ...
		//METODOS PARA DEVOLVER ATRIBUTOS
		// friend unsigned short prec_(void) const;
		// friend unsigned short effsize(void) const;
		// friend bool is_negative(void) const;


		
		~bignum();  //adentro liberar espacio
		bignum(); //prec x defecto - Inicializado en 0
		//bignum(const unsigned short precision);     //util para resultado metodos
		bignum(const int &n);     //util para resultado metodos
		bignum(const std::string &, const unsigned short p );   //"12315", p>=size(str+sign)
		bignum(const bignum &);  //constr copia
		bignum(const char* , const unsigned short p);
		//bignum(int const &);
		//bignum(int const &, const unsigned short p);



		friend const bignum operator+(const bignum&, const bignum&);  // b1 + b2
		friend const bignum operator-(const bignum& b1, const bignum& b2); // b1 - b2
		friend const bignum operator-(const bignum& b1); // -b1
		//friend bignum &operator*(const bignum&, const bignum&);  //p =pmax{p1,p2}
		//friend bignum &operator*(const bignum&, const bignum&);  //p =pmax{p1,p2}

		const bignum & operator=(const bignum &b);
		const bignum & operator=(const int &n);
		
		// ----- COMPARADORES ------
		friend bool operator<(bignum const &b1, bignum const &b2); // b1 < b2
		friend bool operator>(bignum const &b1, bignum const &b2); // b1 > b2
		friend bool operator==(bignum const &b1, bignum const &b2); // b1 == b2

		friend std::ostream& operator<<(std::ostream&, const bignum&);
		friend std::istream& operator>>(std::istream&, bignum&);
		
		
};

#endif