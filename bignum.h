#ifndef _BIGNUM_H_INCLUDED_
#define _BIGNUM_H_INCLUDED_

#include <iostream>
#include <string>

#define PRECISION_DEFAULT 10

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

    public:
    // ...

		~bignum();   //adentro liberar espacio
		bignum(); //prec x defecto - Inicializado en 0
		bignum(const unsigned short precision);     //util para resultado metodos
		bignum(const std::string &, const unsigned short precision);   //"12315", p>=size(str+sign)
		bignum(const bignum &);  //constr copia
		bignum(const char* s, const unsigned short p);
		bignum(std::string& s_, const unsigned short p);

		friend const bignum operator+(const bignum&, const bignum&);  //p =pmax{p1,p2}
		friend const bignum operator-(const bignum& b1, const bignum& b2);
		friend const bignum operator-(const bignum& b1);
		//friend bignum &operator*(const bignum&, const bignum&);  //p =pmax{p1,p2}
		//friend bignum &operator*(const bignum&, const bignum&);  //p =pmax{p1,p2}

		//friend bignum &operator=(const bignum &);
		
		friend bool operator<(bignum const &b1, bignum const &b2);
		friend bool operator>(bignum const &b1, bignum const &b2);
		friend bool operator==(bignum const &b1, bignum const &b2);

		friend std::ostream& operator<<(std::ostream&, const bignum&);
		friend std::istream& operator>>(std::istream&, bignum&);
};

#endif