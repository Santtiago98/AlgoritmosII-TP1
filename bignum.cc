#include <iostream>
#include <string>
#include <algorithm>
#include <math.h> 

#include "bignum.h"

using namespace std;



const bignum operator+(const bignum& b1, const bignum& b2){
	// A DESARROLLAR JUNTO AL RETURN
	
	
	if( ( b1.negative == true ) & ( b2.negative == true ) ){

		return -((-b1)+(-b2));
		
	}
	
	else if( ( b1.negative == true ) & ( b2.negative == false ) ){
	
		return b2 - (-b1);
		
	}
	
	else if( ( b1.negative == false ) & ( b2.negative == true ) ){
	
		return b1 - (-b2) ;
		
	}
	
	unsigned short p = max_precision( b1 , b2 );
	
	unsigned short aux=0; //variable auxiliar para guardar cada valor de la iteración
	unsigned short carry = 0;	//carry de la suma de cada digito
	
	bignum b3(p);
	
	for( int i=0 ; ( i < b1.precision )  & ( i < b2.precision) ; i++ ){
		
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

unsigned short min_precision(const bignum& b1, const bignum& b2){
	
	unsigned short p = b1.precision;
	
	if ( b2.precision < p ){
		p = b2.precision;
	}
	
	return p;
}

unsigned short max_size(const bignum& b1, const bignum& b2){
	
	unsigned short eff = b1.effective_size;
	
	if ( b2.effective_size > eff ){
		eff = b2.effective_size;
	}
	
	return eff;
}

unsigned short min_size(const bignum& b1, const bignum& b2){
	
	unsigned short eff = b1.effective_size;
	
	if ( b2.effective_size < eff ){
		eff = b2.effective_size;
	}
	
	return eff;
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
	

	
	if( ( b1.negative == true ) & ( b2.negative == false ) ){
	
		return -((-b1)+b2);
	}
	
	if( ( b1.negative == false ) & ( b2.negative == true ) ){
	
		return (b1+(-b2));
		
	}
	
	if( ( b1.negative == true ) & ( b2.negative == true ) ){
	
		return (b1+(-b2));
		
	}
	
	if( b2 > b1 ){
		
		return -(b2-b1);
		
	}
	
	//---- CASO BASE ---- //
	// b1 > b2
	unsigned short p = max_precision( b1 , b2 );
	unsigned short carry = 0;
	
	bignum b3(p);
	
	for( int i=0 ; i < b2.effective_size ; i++ ){
		//effective_size es siempre menor o igual a precision
		if( (b1.digits[i] - carry) < b2.digits[i] ){
			
			b3.digits[i] = 10 + b1.digits[i] - carry - b2.digits[i];
			carry = 1;
			
		}
		else{
			
			b3.digits[i] = b1.digits[i] - carry - b2.digits[i];
			carry = 0;
			
		}
		
	}
	
	for(int i=b2.effective_size  ; i < b1.effective_size ; i++ ){
		
		if( (b1.digits[i] - carry) < 0 ){
			
			b3.digits[i] = 10 + b1.digits[i] - carry;
			carry = 1;
			
		}
		else{
			
			b3.digits[i] = b1.digits[i] - carry;
			carry = 0;
			
		}
		
	}

	return b3;
}

const bignum operator-(const bignum& b1){
	
	bignum b2(b1);
	bignum b_0(1);
	
	
	if( b1 == b_0 ){
		
		return b2;
		
	}
	
	b2.negative = !(b1.negative);

	return b2;
}


const bignum operator*(const bignum&, const bignum& b){
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

bignum::bignum() : effective_size(0) , negative(false) {
	
	//bignum(PRECISION_DEFAULT);
	precision = PRECISION_DEFAULT;
	
	digits = new unsigned short[precision];
	
	for(int i=0 ; i < precision ; i++){
		digits[i] = 0;
	}
}

bignum::bignum(unsigned short p) : precision(p) , effective_size(0) , negative(false) {
	
	digits = new unsigned short[precision];
	
	for( int i=0 ; i < precision ; i++){
		digits[i] = 0;
	}
	
}

bignum::bignum(bignum const &b) : precision(b.precision) , effective_size(b.effective_size) , negative(b.negative){
	
	digits = new unsigned short[precision];
	
	for( int i=0 ; i < precision ; i++){
		digits[i] = b.digits[i];
	}
	
}


// bignum::bignum(int const &n) : precision(PRECISION_INT){
	
	// digits = new unsigned short[precision];
	// int aux = 0;
	
	// if( n < 0 ){
		
		// negative = true;
		// aux = -n;
		
	// }
	// else{
		
		// negative = false;
		// aux = n;
		
	// }
	
	// for( int i=0 ; i < precision ; i++){
		
		// digits[i] = aux%10;
		// aux -= aux%10;
		// aux /= 10;
		
		
		// if(  ){
			
			
			
		// }

	// }
	
// }

/*
bignum::bignum(const char* s, const unsigned short p) : precision(p){
	
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


bignum::bignum(std::string const & s_, const unsigned short p) : precision(p){
	
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
	
	if( int( s.length() ) > precision + neg ){
		//salir por falla
	}
	
	for(long unsigned int i=0  ; ( i <  s.length()  - neg )  & ( i < precision ) ; i++ ){
		
		if( ( s[ i+neg ] < 48 ) | ( s[ i+neg ] > 57 )  ){
			
			digits[i] = 0;
			//salir por falla
			
		}
		else{
			
			digits[i] = s[ i+neg ]-48;
			
		}
	}
	
	for(long unsigned int i=0  ; i + s.length() - neg < precision ; i++ ){
		
		digits[ i + s.length() - neg ] = 0;
		
	}
	
	effective_size = size(*this);

}

bignum::~bignum(){
	
	delete []digits;
}

bool operator<(bignum const &b1, bignum const &b2){
	
	if(  b1.negative & !b2.negative ){
		
		return true;
		
	}
	
	else if(  !b1.negative & b2.negative ){
		
		return false;
		
	}
	
	if( b1.effective_size > b2.effective_size ){
		
		return false;
		
	}
	
	else if ( b1.effective_size < b2.effective_size ){
		
		return true;
		
	}
	
	else if ( b1.effective_size == b2.effective_size ){
		
		for ( int i=b1.effective_size ; i >= 0 ; i-- ){
			
			if( b1.digits[i] > b2.digits[i] ){
				
				if( b1.negative ){
					
					return true;
					
				}
				
				return false;
				
			}
			
			else if( b1.digits[i] < b2.digits[i] ){
				
				if( b1.negative ){
					
					return false;
					
				}
				
				return true;
				
			}
			
		}
		
	}
	
	return false;
}

bool operator>(bignum const &b1, bignum const &b2){
	
	if( b1 == b2 ){
		
		return false;
		
	}
	
	else{
		
		return !( b1 < b2 );
		
	}
	
}

bool operator==(bignum const &b1, bignum const &b2){
	
	if(  b1.negative != b2.negative ){
		
		return false;
		
	}
	
	if( b1.effective_size != b2.effective_size ){
		
		return false;
		
	}
	
	else if ( b1.effective_size == b2.effective_size ){
		
		for ( int i=b1.effective_size ; i >= 0 ; i-- ){
			
			if( b1.digits[i] != b2.digits[i] ){
				
				return false;
				
			}
			
		}
		
	}
	
	return true;
	
}

const bignum & bignum::operator=(const bignum &b){
	
	delete [] digits;
	digits = new unsigned short[b.precision];
	precision = b.precision;
	negative = b.negative;
	effective_size = b.effective_size;
	
	for(int i=0; i<precision ; i++ ){
		
		digits[i] = b.digits[i];
		
	}
	
	return *this;
	
}

unsigned short size( bignum const &b ){	

	for( int i = b.precision - 1 ; i >= 0 ; i-- ){
		
		if( b.digits[i] !=0 ){
			
			return i+1;
			
		}
		
	}
	
	return 0;
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