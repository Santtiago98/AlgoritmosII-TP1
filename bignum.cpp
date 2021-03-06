#include <iostream>
#include <string>
#include <algorithm>
#include <math.h> 
#include <map>
#include <utility>
#include <vector>
#include "bignum.h"
#include "strategy.h"

using namespace std;

// ------------------ METODOS PRIVADOS USADOS INTERNAMENTE ------------------ //

unsigned long int max_size(const bignum& b1, const bignum& b2){
	
	unsigned long eff = b1.bn_length;
	
	if ( b2.bn_length > eff ){
		eff = b2.bn_length;
	}
	return eff;
	
}

unsigned long int min_size(const bignum& b1, const bignum& b2){
	
	unsigned long int eff = b1.bn_length;
	
	if (b2.bn_length < eff){
		eff = b2.bn_length;
	}
	
	return eff;
}

const bignum bn_exp_10(unsigned long expo){
	
	bignum b;
	
	std::string s = std::string( expo+1 , '0');
	
	s[0] = '1';
	
	b = bignum(s);
	
	return b;
	
}

// ------------------ METODOS PARA DEVOLVER ATRIBUTOS ------------------ //


bool bignum::bad() const {
	
	if(digits == NULL){
		//si está mal formado el bignum, el puntero está a NULL
		return true;
	}
	else{
		return false;
	}

}

// ------------------ DESTRUCTOR ------------------ //

bignum::~bignum(){
	
	if( digits != NULL){
		delete []digits;
	}
    
}

// ------------------ CONSTRUCTORES ------------------ //

bignum::bignum() : digits(NULL) , bn_length(0) , negative(false), strategy_ptr(NULL)
{
	
}

bignum::bignum(const int n, Strategy * str_ptr){
	
//------	Creación de un bignum a partir de un int -------//
	strategy_ptr = str_ptr;
    
	if( n==0 ){
		
		bn_length = 1;
		digits = new unsigned short[bn_length];
		//se setea en 0
		digits[0] = 0;
		negative = false;
		return;
		
	}
	
	unsigned short* aux_digits = new unsigned short[BIGNUM_PRECISION_INT]; //se pide memoria para el vector de ushorts con maximo largo auxiliar
	int aux = 0; //variable auxiliar para ir guardando resultado
	
	// ---- SETEO DE SIGNO ---- //
	// se toma en cuenta solo con la parte absoluta de n
	if( n < 0 ){
		negative = true;
		aux = -n;
	}
	else{
		negative = false;
		aux = n;
	}
	
	unsigned long effective_size=0;
	//int i=0;
	
	// ---- LOOP ---- //
	for( unsigned long i=0 ; i < BIGNUM_PRECISION_INT ; i++){
		//si aux es 0 se sale del loop
		if( aux == 0 ){
			break;
		}
        
		aux_digits[i] = aux%10;
		aux -= aux%10;
		aux /= 10;
		effective_size ++;		
	}
	
	bn_length = effective_size;
	digits = new unsigned short[bn_length];
	
	for( unsigned long i=0 ; i < bn_length ; i++){
		digits[i] = aux_digits[i];
	}	
	
	delete[] aux_digits;
	aux_digits = NULL;
	
}

bignum::bignum(std::string const & s_,  Strategy * str_ptr){

	
	int neg = 0;
	std::string s(s_);
	strategy_ptr = str_ptr;
    
	if( s[0] == '-' ){
		negative = true;
		neg = 1;
	}
	else if( s[0] == '+' ){
		negative = false;
		neg = 1;
	}
	else{
		negative = false;
		neg = 0;
	}
	
	if( s.length() - neg <= 0  ){
		digits = NULL,
		bn_length = 0;
		negative = false;
		return;
	}
	
	bn_length = s.length() - neg ;
	digits = new unsigned short[ bn_length ];
	std::reverse(s.begin() + neg , s.end() ); //se dan vuelta los numeros
	
	for( unsigned long i=0 ; i < bn_length ; i++ ){
		
		// 48 representa '0', 57 representa '9'
		
		if( ( s[ i+neg ] < '0' ) | ( s[ i+neg ] > '9' )  ){
			delete[] digits;
			digits = NULL;
			bn_length = 0;
			negative = false;
			break;
		}
		else{
			digits[i] = s[ i+neg ]-48; //restandole 48 queda el digito que necesito como ushort
		}
	}
    
}

bignum::bignum(const char * c_arr,  Strategy * str_ptr){
	
	std::string s(c_arr); //se castea a string
	digits = NULL; //si no se pone en NULL, la asignación fallará
	bn_length = 0;
	bignum b1(s,str_ptr); //se usa el constructor de string
	*this = b1;
	
}

bignum::bignum(bignum const &b){
	
	// CONSTRUCTOR COPIA //
	strategy_ptr = b.strategy_ptr;
    
	if( b.digits == NULL ){
		digits = NULL;
		bn_length = 0;
		negative = false;
		return;
		
	}
    
	bn_length = b.bn_length;
	negative = b.negative;
	
	digits = new unsigned short[bn_length];
	
	for( unsigned long i=0 ; i < bn_length ; i++){
		digits[i] = b.digits[i];
	}
	
}

bignum const bignum::operator+=(const bignum&b2){
	
	bignum aux = *this;

	*this = aux + b2;
	
	return *this;
	
}

bignum const bignum::operator-=(const bignum&b2){
	
	bignum aux = *this;

	*this = aux - b2;
	
	return *this;
	
}

bignum const bignum::operator*=(const bignum&b2){
	
	bignum aux = *this;

	*this = aux * b2;
	
	return *this;
	
}

bignum const bignum::operator+=(const int n){
	
	bignum b2(n);
	bignum aux = *this;
	
	*this = aux + b2;
	
	return *this;
	
}

bignum const bignum::operator-=(const int n){
	
	bignum b2(n);
	bignum aux = *this;
	
	*this = aux - b2;
	
	return *this;
	
}

bignum const bignum::operator*=(const int n){
	
	bignum b2(n);
	bignum aux = *this;
	
	*this = aux * b2;
	
	return *this;
	
}

// ------------------ OPERACIONES ALGEBRAICAS ------------------ //

const bignum operator+(const bignum& b1, const bignum& b2){
	
	bignum b3;
    b3.strategy_ptr = b1.strategy_ptr;
    
	if( (b1.digits == NULL) | (b2.digits == NULL) ){
		return b3;
	}
	
	if( ( b1.negative == true ) & ( b2.negative == true ) ){
		return -((-b1)+(-b2));
	}
	
	else if( ( b1.negative == true ) & ( b2.negative == false ) ){
		return b2 - (-b1);
	}
	
	else if( ( b1.negative == false ) & ( b2.negative == true ) ){
		return b1 - (-b2);
	}
	
	if( b2 > b1 ){
		return b2 + b1;
	}
	
	// --- SI SE LLEGA ACA AMBOS POSITIVOS Y B1 > B2 --- //
	
	unsigned short aux = 0; //variable auxiliar para guardar cada valor de la iteración
	unsigned short carry = 0;	//carry de la suma de cada digito
	unsigned short* aux_digits = new unsigned short[b1.bn_length + 1];
	unsigned long effective_size = 0;
	
	for( unsigned long i=0 ; i < b2.bn_length ; i++ ){
		
		aux = b1.digits[i] + b2.digits[i] + carry;	//sumo los digitos y el valor de carry
		aux_digits[i] = aux%10;	//me quedo con el primer digito
		carry = ( aux - aux_digits[i] ) / 10 ;	//determino el siguiente carry
		effective_size++;
		
	}
	
	for( unsigned long i=b2.bn_length; i<b1.bn_length ; i++ ){
		aux = b1.digits[i] + carry;
		aux_digits[i] = aux%10;
		carry = ( aux - aux_digits[i] ) / 10 ;
		effective_size++;
	}
	
	if( carry > 0 ){
		aux_digits[effective_size] = carry;
		effective_size++;
		carry = 0;
	}
	
	b3.bn_length = effective_size;
	b3.digits = new unsigned short[b3.bn_length];
	b3.negative = false;
	
	for( unsigned long i=0 ; i < b3.bn_length ; i++){
		b3.digits[i] = aux_digits[i];
	}
	
	delete[] aux_digits;
	aux_digits = NULL;
	
	return b3;
	
}

const bignum operator-(const bignum& b1, const bignum& b2){
	
	bignum b3;
    b3.strategy_ptr = b1.strategy_ptr;
	
	if( (b1.digits == NULL) | (b2.digits == NULL) ){
		return b3;
	}
	
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
		return - (b2-b1) ;
	}
	
	//---- CASO BASE ---- //
	// b1 > b2
	unsigned short carry = 0;	//carry de la suma de cada digito
	unsigned short* aux_digits = new unsigned short[ b1.bn_length ];
	unsigned long effective_size = 0;
	
	
	for( unsigned long i=0 ; i < b2.bn_length ; i++ ){
		
		if( (b1.digits[i] - carry) < b2.digits[i] ){
			
			aux_digits[i] = 10 + b1.digits[i] - carry - b2.digits[i];
			carry = 1;
			
		}
		else{
			
			aux_digits[i] = b1.digits[i] - carry - b2.digits[i];
			carry = 0;
			
		}
		effective_size++;
		
	}
	
	for( unsigned long i=b2.bn_length  ; i < b1.bn_length ; i++ ){
		
		if( (b1.digits[i] - carry) < 0 ){
			
			aux_digits[i] = 10 + b1.digits[i] - carry;
			carry = 1;
			
		}
		else{
			
			aux_digits[i] = b1.digits[i] - carry;
			carry = 0;
			
		}
		effective_size++;
		
	}	
	
	b3.bn_length = 0;
	
	for( unsigned long i = 0 ; i < effective_size ; i++ ){
		
		if( aux_digits[effective_size-i-1] !=0 ){
			b3.bn_length = effective_size-i;
			break;
		}
		
	}
	
	if ( b3.bn_length == 0 ){
		b3.bn_length = 1;
	}

	b3.digits = new unsigned short[b3.bn_length];
	b3.negative = false;
	
	for( unsigned long i=0 ; i < b3.bn_length ; i++){
		b3.digits[i] = aux_digits[i];
	}
	
	delete[] aux_digits;
	aux_digits = NULL;
	
	return b3;
	
}

const bignum operator-(const bignum& b1){
	
	bignum b2 = b1;
	bignum b_0 = 0;
	
	if( b1.digits == NULL ){
		return b2;
	}
	
	if( b1 == b_0 ){
		return b2;
	}
	
	b2.negative = !(b1.negative);
	
	return b2;
}

const bignum operator*(const bignum& b1, const bignum& b2){
	
    bignum b3;
    
    if (!b1.strategy_ptr){
       return b3;
       }
       
    b3 = (b1.strategy_ptr)->multiply_strat(b1,b2);
    b3.strategy_ptr = b1.strategy_ptr;
	return b3;
}

const bignum operator/(const bignum& b1_, const bignum& b2_){
	
	int base_int = 10;
	bignum base = base_int;
	bignum b1=b1_;
	b1.negative = false;
	bignum b2=b2_;
	b2.negative = false;
	
	bignum zero = 0;
	zero.strategy_ptr = b1_.strategy_ptr;
	bignum one = 1;
	one.strategy_ptr = b1_.strategy_ptr;
	bignum b3;
	b3.strategy_ptr = b1_.strategy_ptr;
	
	if( (b1_.digits == NULL) || (b2_.digits == NULL) ){
		return b3;
	}
	
	if( b2 > b1 ){
		return zero;
	}
	
	if( b2 == one ){
		return b1;
	}
	
	//b1 > b2
	
	bignum q = 0;
	bignum r = 0;
	bignum d = 0;
	int beta;
	bignum m_beta = 0;
	bignum aux = 0;
	
	for( unsigned long i = 0 ; i < (b2.bn_length - 1 ) ; i++ ){
		
		aux.digits[0] = b1.digits[ b1.bn_length - i - 1 ];
		r += bn_mult_pow10_( aux , b2.bn_length - i - 2 );
		
	}
	
	// cout << ";r_-1=" << r <<";";
	
	for( unsigned long i = 0 ; i < (b1.bn_length - b2.bn_length+ 1) ; i++ ){

		d = bn_mult_pow10_( r , 1 ) + b1.digits[ b1.bn_length - (b2.bn_length - 1) - i - 2 + 1 ];
		
		
		for(beta = 0; beta < base_int ; beta++){
			
			m_beta = b2;
			m_beta *= beta;

			if( ( m_beta <= d ) && ( m_beta > (d-b2) ) ){
				break;
			}
			
		}

		r = d - m_beta;

		q = bn_mult_pow10_(q,1);
		q += beta;

		
	}

	b3 = q;
	b3.strategy_ptr = b1_.strategy_ptr;
	
	if( ( b1_.negative & !b2_.negative) || (!b1_.negative & b2_.negative) ){
	
		b3.negative = true;
		
	}
	
	else{
		
		b3.negative = false;
		
	}
	
	return b3;
	
}



// ------------------ ASIGNACIONES ------------------ //

const bignum & bignum::operator=(const bignum &b){
	strategy_ptr = b.strategy_ptr;
    
	if( this == &b ){
		return *this;
	}
	
	if( digits != NULL  ){
		delete []digits;
	}
	
	if( b.digits == NULL ){
		digits = NULL;
		bn_length = 0;
		negative = false;
		return *this;
	}

	digits = new unsigned short[b.bn_length];
	bn_length = b.bn_length;
	negative = b.negative;
	
	for( unsigned long i=0 ; i < bn_length ; i++ ){
		digits[i] = b.digits[i];
	}
	
	return *this;
}

const bignum & bignum::operator=(const int n){

    
	if( digits != NULL  ){
		delete []digits;
	}

	bignum b1(n,this->strategy_ptr);
	
	*this = b1;
	
	return *this;
	
}

// ------------------ COMPARADORES ------------------ //

bool operator<(bignum const &b1, bignum const &b2){
	
	if( (b1.digits == NULL) || (b2.digits == NULL) ){
	
		return false;
		
	}
	
	if(  b1.negative && !b2.negative ){
		
		return true;
		
	}
	
	else if(  !b1.negative && b2.negative ){
		
		return false;
		
	}
	
	if( b1.bn_length > b2.bn_length ){
		
		return false;
		
	}
	
	else if ( b1.bn_length < b2.bn_length ){
		
		return true;
		
	}
	
	else if ( b1.bn_length == b2.bn_length ){
		
		for ( unsigned long i=0 ; i < b1.bn_length ; i++ ){
			
			if( b1.digits[b1.bn_length - i - 1] > b2.digits[b1.bn_length - i - 1] ){
				
				if( b1.negative ){
					
					return true;
					
				}
				
				return false;
				
			}
			
			else if( b1.digits[b1.bn_length - i - 1] < b2.digits[b1.bn_length - i - 1] ){
				
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
	
	if( (b1.digits == NULL) || (b2.digits == NULL) ){
	
		return false;
		
	}
	
	if( b1 == b2 ){
		
		return false;
		
	}
	
	else{
		
		return !( b1 < b2 );
		
	}
	
}

bool operator==(bignum const &b1, bignum const &b2){
	
	if( (b1.digits == NULL) || (b2.digits == NULL) ){
	
		return false;
		
	}
	
	if(  b1.negative != b2.negative ){
		
		return false;
		
	}
	
	if( b1.bn_length != b2.bn_length ){
		
		return false;
		
	}
	
	else if ( b1.bn_length == b2.bn_length ){
		
		for ( unsigned long i=0 ; i < b1.bn_length ; i++ ){
			
			if( b1.digits[b1.bn_length - i - 1] != b2.digits[b1.bn_length - i - 1] ){
				
				return false;
				
			}
			
		}
		
	}
	
	return true;
	
}

bool operator>=(bignum const &b1, bignum const &b2){
	
	if( (b1.digits == NULL) || (b2.digits == NULL) ){
	
		return false;
		
	}
	
	if( (b1 == b2) || (b1>b2) ){
		
		return true;
		
	}
	
	else{
		
		return false;
		
	}
	
}

bool operator<=(bignum const &b1, bignum const &b2){
	
	if( (b1.digits == NULL) || (b2.digits == NULL) ){
	
		return false;
		
	}
	
	if( (b1 == b2) || (b1<b2) ){
		
		return true;
		
	}
	
	else{
		
		return false;
		
	}
	
}



// ------------------ LECTURA/ESCRITURA ------------------ //

std::ostream& operator<<(std::ostream& os, const bignum& b){
	// A DESARROLLAR JUNTO AL RETURN
	
	
	if( b.digits == NULL ){
		os << BIGNUM_MSG_ERR_BAD;
		return os;
	}
	
	if ( b.negative ){
		os << "-";
	}
	
	
	for( unsigned long i = 0 ; i < b.bn_length  ; i++ ){
		os << b.digits[ b.bn_length - i - 1 ];
	}
	
	return os;
}

std::istream& operator>>(std::istream& is, bignum& b){
	
	if( b.digits != NULL ){
		
		delete [] b.digits;
		b.digits = NULL;
		b.bn_length = 0;
		b.negative = false;
		
	}
	
	std::string s = "";
	char c;
	
	is >> c ;
	
	if( (c == '-') || (c == '+') ){
		s+=c;
		is >> c;
		if( ( c < '0' ) || ( c > '9' )  ){
			b.digits = NULL;
			b.bn_length = 0;
			b.negative = false;
			return is;
		}
		s+=c;
	}
	else if( (c >= '0') || (c <= '9')  ){
		s+=c;		
	}
	else{
		b.digits = NULL;
		b.bn_length = 0;
		b.negative = false;
		return is;
	}
	
	while( is >> c ){
		
		if( ( c < '0' ) || ( c > '9' )  ){
			b = bignum(s,b.strategy_ptr);
			return is;
		}
		else{
			s+=c;
		}
		
	}
	
	return is;
	
}

void bignum::set_strategy( Strategy *str_ptr){
    if(this->strategy_ptr){
        delete this->strategy_ptr;
    }
    this->strategy_ptr = str_ptr;
    
}

const bignum bn_mult_pow10_(const bignum & b1, unsigned long n){
	
	bignum b;
	bignum zero = 0;
	b.strategy_ptr = b1.strategy_ptr;
    
	if( b1.digits == NULL ){
        return b;
	}
	
	if( b1 == zero ){
		return b1;
	}
	
	if( n==0 ){
		return b1;
	}	
	
	b.bn_length = b1.bn_length + n; // se le agregan n 0s atras
	b.digits = new unsigned short[b.bn_length];
	b.negative = b1.negative;
	
	for( unsigned long int i=0 ; i < n ; i++ ){
		b.digits[i] = 0;
	}
	
	for( unsigned long int i=0 ; i < b1.bn_length ; i++ ){
		b.digits[n + i] = b1.digits[i];
	}
	
	
	return b;
	
}