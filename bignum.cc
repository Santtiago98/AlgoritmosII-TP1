#include <iostream>
#include <string>
#include <algorithm>

#include "bignum.h"

using namespace std;



const bignum operator+(const bignum& b1, const bignum& b2){
	// A DESARROLLAR JUNTO AL RETURN
	
	unsigned short p = max_precision( b1 , b2 );
	
	bignum b3(p);
	
	if( b1.negative == true ){
		if( b2.negative == true ){
			
			b3 = (-b1)+(-b2);
			b3.negative = true;
			
		}
		else{
			
			//b3 =  ;
			
		}
		return b3;
	}
	
	if( b2.negative == true ){
		if( b1.negative == true ){
			
			b3 = (-b1)+(-b2);
			b3.negative = true;
			
		}
		else{
			
			//b3 =  ;
			
		}
		return b3;
	}
	
	
	unsigned short aux=0; //variable auxiliar para guardar cada valor de la iteración
	unsigned short carry = 0;	//carry de la suma de cada digito
	
	for( int i=0 ; i < b1.precision & i < b2.precision; i++ ){
		
		aux = b1.digits[i] + b2.digits[i] + carry;	//sumo los digitos y el valor de carry
		b3.digits[i] = aux%10;	//me quedo con el primer digito
		carry = ( aux - b3.digits[i] ) / 10 ;	//determino el siguiente carry
		
	}
	
	if( b1.precision < b2.precision ){
		
		for(int i=0; i+b1.precision<b3.precision ; i++ ){
			
			b3.digits[ i+b1.precision ] = b2.digits[i+b1.precision] + carry;
			carry = 0;
			
		}
		
	}
	else if( b2.precision < b1.precision ){
		
		for(int i=0; i+b2.precision<b3.precision ; i++ ){
			
			b3.digits[ i+b2.precision ] = b1.digits[i+b2.precision] + carry;
			carry = 0;
			
		}
		
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

/*
complejo const
operator+(complejo const &x, complejo const &y)
{
	complejo z(x.re_ + y.re_, x.im_ + y.im_);
	return z;
}
*/

/*
const bignum& operator-(const bignum& b1, const bignum& b2){
	
	
	// A DESARROLLAR JUNTO AL RETURN
	return b1;
}

*/

const bignum operator-(const bignum& b1, const bignum& b2){
	// A DESARROLLAR JUNTO AL RETURN
	
	unsigned short p = max_precision( b1 , b2 );
	
	bignum b3(p);
	
	if( b1.negative == true ){
		if( b2.negative == false ){
			
			b3 = -(-b1)+(-b2);
			b3.negative = true;
			
		}
		else{
			
			//b3 =  ;
			
		}
		return b3;
	}
	
	if( b2.negative == false ){
		if( b1.negative == true ){
			
			b3 = b1+(-b2);
			b3.negative = false;
			
		}
		else{
			
			//b3 =  ;
			
		}
		return b3;
	}

	return b3;
}

const bignum operator-(const bignum& b1){
	
	bignum b2(b1);
	
	b2.negative = !b1.negative;

	return b2;
}


const bignum& operator*(const bignum&, const bignum& b){
	// A DESARROLLAR JUNTO AL RETURN
	return b;
}

std::ostream& operator<<(std::ostream& os, const bignum& b){
	// A DESARROLLAR JUNTO AL RETURN
	
	//cout << "print bignum:" << endl;
	//cout << "precision " << b.precision << endl;
	
	bool print = false;
	
	if ( b.negative ){
		os << "-";
	}
	
	
	for( int i = b.precision - 1 ; i >= 0 ; i-- ){
		if( !print ){
			
			if( b.digits[i] !=0 ){
				
				os << b.digits[i];
				print = true;
				
			}
			
		}
		else{
			
			os << b.digits[i];
			
		}
	}
	
	if( !print ){
		
		os << 0 ;
		
	}
	
	return os;
}

std::istream& operator>>(std::istream& is, bignum& b){
	// A DESARROLLAR JUNTO AL RETURN
	return is;
}

bignum::bignum() : negative(false)
{		
	//bignum(PRECISION_DEFAULT);
	precision = PRECISION_DEFAULT;
	
	digits = new unsigned short[precision];
	
	for(int i=0 ; i < precision ; i++){
		digits[i] = 0;
	}
}

bignum::bignum(unsigned short p) : precision(p) , negative(false)
{	
	digits = new unsigned short[precision];
	
	for( int i=0 ; i < precision ; i++){
		digits[i] = 0;
	}
	
}

bignum::bignum(bignum const &b) : precision(b.precision) , negative(b.negative)
{	
	digits = new unsigned short[precision];
	
	for( int i=0 ; i < precision ; i++){
		digits[i] = b.digits[i];
	}
	
}


/*
bignum::bignum(const char* s, const unsigned short p) : precision(p)
{
	digits = new unsigned short[precision];
	int i=0;
	int len_s=0;
	
	for( i=0 ; s[i] != '\0' ; i++ ){
		
	}
	
	len_s = i;
	
	if( s[0] == '-' ){
		
		negative = true;
		i = 1;
		
	}
	else{
		
		negative = false;
		i = 0;
		
	}
	
	if( (negative & len_s > precision+1) | ( !negative & len_s > precision ) ){
		//i=i/0;
	}
	
	std::reverse( s+i , s + len_s );
	
	for( i=0  ; i < len_s ; i++ ){
		
		if( s[i] < 48 | s[i] > 57 ){
			
			digits[i] = 0;
			//i=i/0;
			
		}
		else{
			
			digits[i] = s[i]-48;
			
		}
	}

}
*/


bignum::bignum(std::string& s_, const unsigned short p) : precision(p)
{
	digits = new unsigned short[precision];
	
	int neg = 0;
	std::string s(s_);
	
	if( s[0] == '-' ){
		
		negative = true;
		neg = 1;
		
	}
	else{
		
		negative = false;
		neg = 0;
		
	}
	
	std::reverse(s.begin() + neg , s.end() );
	
	if( s.length() > precision + neg ){
		//salir por falla
	}
	
	for(int i=0  ; i < s.length() - neg & i < precision ; i++ ){
		
		if( s[ i+neg ] < 48 | s[ i+neg ] > 57 ){
			
			digits[i] = 0;
			//salir por falla
			
		}
		else{
			
			digits[i] = s[ i+neg ]-48;
			
		}
	}
	
	for(int i=0  ; i + s.length() - neg < precision ; i++ ){
		
		digits[ i + s.length() - neg ] = 0;
		
	}

}

bignum::~bignum()
{
	delete []digits;
}

/*

complejo::complejo(double r) : re_(r), im_(0)
{
}

complejo::complejo(double r, double i) : re_(r), im_(i)
{
}

complejo::complejo(complejo const &c) : re_(c.re_), im_(c.im_)
{
}


*/