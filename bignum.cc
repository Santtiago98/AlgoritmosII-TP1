#include <iostream>
#include "bignum.h"
#define PRECISION_DEFAULT 10

using namespace std;

bignum operator+(const bignum& b1, const bignum& b2){
	// A DESARROLLAR JUNTO AL RETURN
	
	unsigned short p = max_precision( b1 , b2 );
	
	bignum b3(p);
	
	if( b1.negative = true ){
		if( b2.negative = true ){
			
			b3 = (-b1)+(-b2);
			b3.negative = true;
			
		}
		else{
			
			//b3 =  ;
			
		}
		return b3;
	}
	
	if( b2.negative = true ){
		if( b1.negative = true ){
			
			b3 = (-b1)+(-b2);
			b3.negative = true;
			
		}
		else{
			
			//b3 =  ;
			
		}
		return b3;
	}
	
	
	unsigned short aux; //variable auxiliar para guardar cada valor de la iteración
	unsigned short carry = 0;	//carry de la suma de cada digito
	
	for( int i; i < b3.precision ; i++ ){
		
		aux = b1.digits[i] + b2.digits[i] + carry;	//sumo los digitos y el valor de carry
		b3.digits[i] = aux%10;	//me quedo con el primer digito
		carry = ( aux - b3.digits[i] ) / 10 ;	//determino el siguiente carry
		
	}
	
	b3.negative = false;
	
	return b3;
	
}

unsigned short max_precision(const bignum& b1, const bignum& b2){
	
	unsigned short p = b1.precision;
	
	if ( b2.precision > p ){
		p = b2.precision;
	}
	
	return p;
}

complejo const
operator+(complejo const &x, complejo const &y)
{
	complejo z(x.re_ + y.re_, x.im_ + y.im_);
	return z;
}

bignum operator-(const bignum& b1, const bignum& b2){
	// A DESARROLLAR JUNTO AL RETURN
	return b1;
}

bignum operator*(const bignum&, const bignum& b){
	// A DESARROLLAR JUNTO AL RETURN
	return b;
}
std::ostream& operator<<(std::ostream& os, const bignum& b){
	// A DESARROLLAR JUNTO AL RETURN
	return os;
}
std::istream& operator>>(std::istream& is, bignum& b){
	// A DESARROLLAR JUNTO AL RETURN
	return is;
}

bignum::bignum() : negative(false)
{		
	return bignum(PRECISION_DEFAULT)	
}

bignum::bignum(unsigned short p) : precision(p) , negative(false)
{	
	digits = new unsigned short[precision]
	for(int i; i<precision ; i++){
		digits[i] = 0;
	}
	
	return *this;
	
}

bignum::~bignum()
{
	delete []digits;
}

complejo::complejo(double r) : re_(r), im_(0)
{
}

complejo::complejo(double r, double i) : re_(r), im_(i)
{
}

complejo::complejo(complejo const &c) : re_(c.re_), im_(c.im_)
{
}


