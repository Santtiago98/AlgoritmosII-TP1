#include <iostream>
#include <string>
#include <algorithm>
#include <math.h> 

#include "./bignum.h"

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
	
	if( b2>b1 ){
		
		return b2+b1;
		
	}
	
	// --- ASUMO AMBOS POSITIVOS Y B1 > B2 --- //
	
	unsigned short p = max_precision( b1 , b2 );
	
	unsigned short aux=0; //variable auxiliar para guardar cada valor de la iteración
	unsigned short carry = 0;	//carry de la suma de cada digito
	
	bignum b3(std::string("0"),p);
	b3.effective_size = 0;
	
	for( int i=0 ; i < b2.effective_size ; i++ ){
		
		aux = b1.digits[i] + b2.digits[i] + carry;	//sumo los digitos y el valor de carry
		b3.digits[i] = aux%10;	//me quedo con el primer digito
		carry = ( aux - b3.digits[i] ) / 10 ;	//determino el siguiente carry
		b3.effective_size++;
		
	}
	
	for(int i=b2.effective_size; i<b1.effective_size ; i++ ){
		
		aux = b1.digits[ i ] + carry;
		b3.digits[i] = aux%10;
		carry = ( aux - b3.digits[i] ) / 10 ;
		b3.effective_size++;
		
		
	}
	
	if( (carry > 0) & (b3.effective_size < b3.precision) ){
		
		b3.digits[b3.effective_size] = carry;
		b3.effective_size++;
		carry = 0;
		
	}
	else if( carry>0 ){
	
		delete[] b3.digits;
		throw std::range_error("precision is not enough");
		
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
	b3.effective_size = size(b3);
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



/*  Pseudo Cose Multiply with array
multiply(a[1..p], b[1..q], base)                            // Operands containing rightmost digits at index 1
  product = [1..p+q]                                        // Allocate space for result
  for b_i = 1 to q                                          // for all digits in b
    carry = 0
    for a_i = 1 to p                                        // for all digits in a
      product[a_i + b_i - 1] += carry + a[a_i] * b[b_i]
      carry = product[a_i + b_i - 1] / base
      product[a_i + b_i - 1] = product[a_i + b_i - 1] mod base
    product[b_i + p] = carry                               // last digit comes from final carry
  return product
*/

const bignum operator*(const bignum& b1, const bignum& b2){

	unsigned short p = max_precision( b1 , b2 );
	unsigned short carry ;	//carry del producto de cada digito
	int base = 10;

	
	// El producto b1[1..p] y b2[1..q] tiene largo p+q[-1] dependiendo del carry final
	if((b1.effective_size + b2.effective_size)  <= p + 1){
		bignum b3(p);
		
		for(int i = 0; i<b2.effective_size;i++){
			carry=0;
			for(int j = 0 ; j < b1.effective_size ; j++){
				b3.digits[i+j] += carry + b1.digits[j] * b2.digits[i];	
				carry = b3.digits[i+j] / base;
				b3.digits[i+j] = b3.digits[i+j] % base;
			}

			if(! ((i+b1.effective_size == p )  && (carry != 0))) {
				b3.digits[i + b1.effective_size ] = carry;
			}
			
			//Si calculo el producto y la precision no me alcanza para agregar el ultimo carry --> error				
			else{
				delete[] b3.digits;
				throw std::range_error("precision is not enough");
			}
			
		}
		
		//Seteo effective_size y signo del resultado
		b3.effective_size = size(b3);
		if((b1.negative && !b2.negative) || (!b1.negative && b2.negative)  )
			b3.negative = true;

		return b3;
	}

	throw std::range_error("precision is not enough");
}




std::ostream& operator<<(std::ostream& os, const bignum& b){
	// A DESARROLLAR JUNTO AL RETURN
	
	//cout << "print bignum:" << endl;
	//cout << "precision " << b.precision << endl;
	
	if ( b.negative ){
		os << "-";
	}
	
	
	for( int i = b.effective_size - 1 ; i >= 0 ; i-- ){
		
		os << b.digits[i];
		
	}
	
	if( b.effective_size == 0 ){
		
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
	
	 //cout << "creando por bignum(p) " << endl; 
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
    else if (s[0] == '+'){
        negative = false;
        neg = 1;
    }
	else{
		
		negative = false;
		neg = 0;
		
	}
	
	std::reverse(s.begin() + neg , s.end() );
	
	if( int( s.length() ) > precision + neg ){
		throw std::range_error("precision is not enough");
	}
	
	for(long unsigned int i=0  ; ( i <  s.length()  - neg )  & ( i < precision ) ; i++ ){
		
		if( ( s[ i+neg ] < 48 ) | ( s[ i+neg ] > 57 )  ){
			
			digits[i] = 0;
			throw std::invalid_argument("The input numbers should be integers");
			
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

bignum::bignum(const int &n) : precision(PRECISION_INT){
	
//------	Creación de un bignum a partir de un int -------//
	
	digits = new unsigned short[precision]; //se pide memoria para el vector de ushorts que contiene
	int aux = 0; //variable auxiliar para ir guardando resultado
	
	//cout << "POR INT" <<endl;
	// ---- SETEO DE SIGNO ---- //
	if( n < 0 ){
		
		negative = true;
		aux = -n;
		
	}
	else{
		
		negative = false;
		aux = n;
		
	}
	
	// ---- LOOP ---- //
	for( int i=0 ; i < precision ; i++){
		
		if( aux < 10 ){
			
			digits[i] = aux%10;
			effective_size = i+1;
			break;
			
		}
		else{ 

			digits[i] = aux%10;
			aux -= aux%10;
			aux /= 10;

		}
		
		

	}
	
	//return *this;
	
}

const bignum & bignum::operator=(const bignum &b){
	
	delete []digits;
	digits = new unsigned short[b.precision];
	precision = b.precision;
	negative = b.negative;
	effective_size = b.effective_size;
	
	for(int i=0; i<precision ; i++ ){
		
		digits[i] = b.digits[i];
		
	}
	
	return *this;
	
}

const bignum & bignum::operator=(const int &n){
	
	precision = PRECISION_INT;
	delete [] digits;
	digits = new unsigned short[precision];
	int aux = 0;
	
	if( n < 0 ){
		
		negative = true;
		aux = -n;
		
	}
	else{
		
		negative = false;
		aux = n;
		
	}
	
	for( int i=0 ; i < precision ; i++){
		
		cout << "aux = " << aux << endl; 
		digits[i] = aux%10;
		cout << "aux%10 = " << aux%10 << endl;
		aux -= aux%10;
		cout << "aux -= aux%10 = " << aux%10 << endl;
		aux /= 10;
		cout << "aux /= 10 = " << aux%10 << endl;
		
		
		if( aux < 10 ){
			
			digits[i] = aux%10;
			effective_size = i+1;
			break;
			
		}

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


 unsigned short bignum::prec(void) const{	

	 return precision;
 }

 unsigned short bignum::eff_size(void) const{	

	 return effective_size;
 }

 bool bignum::sign() const  {	

	 return !negative;
 }

bool bignum::is_negative() const {
	return negative;
}



