#include <iostream>
#include "bignum.h"
#define PRECISION_DEFAULT 10

using namespace std;

bignum operator+(const bignum& b1, const bignum& b2){
	// A DESARROLLAR JUNTO AL RETURN
	return b1;
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

complejo::complejo(double r) : re_(r), im_(0)
{
}

complejo::complejo(double r, double i) : re_(r), im_(i)
{
}

complejo::complejo(complejo const &c) : re_(c.re_), im_(c.im_)
{
}


complejo::~complejo()
{
	delete []digits
}