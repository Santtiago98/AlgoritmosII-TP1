#include "karatsuba.h"
   
const bignum Karatsuba_multiply::bn_last_digits(const bignum & b1, unsigned long int n){
	
	bignum b;
	b.strategy_ptr = b1.strategy_ptr;
    
	if( (b1.digits == NULL) || ( n > b1.bn_length ) ){
		return b;
	}
	
	if( n==0 ){
		bignum zero = 0;
		zero.strategy_ptr = b1.strategy_ptr;
		return zero;
	}

	b.bn_length = n;
	b.digits = new unsigned short[b.bn_length];
	b.negative = b1.negative;
	
	for( unsigned long int i=0 ; i < n ; i++ ){
		b.digits[i] = b1.digits[b1.bn_length - n + i];
	}

	return b;
	
}

const bignum Karatsuba_multiply::bn_first_digits(const bignum & b1, unsigned long n){
	
	bignum b;
	b.strategy_ptr = b1.strategy_ptr;
	
	if( (b1.digits == NULL) || ( n > b1.bn_length ) ){
		return b;
	}
	
	if( n==0 ){
		bignum zero = 0;
		zero.strategy_ptr = b1.strategy_ptr;
		return zero;
	}
	
	unsigned short* aux_digits = new unsigned short[ n ];
	
	for( unsigned long i=0 ; i < n ; i++ ){
		aux_digits[i] = b1.digits[i];
	}
	
	for( unsigned long i = 0 ; i < n ; i++ ){
		
		if( aux_digits[n-i-1] !=0 ){
			b.bn_length = n-i;
			break;
		}
		
	}
	
	if ( b.bn_length == 0 ){
		b.bn_length = 1;
	}
	
	b.digits = new unsigned short[b.bn_length];
	b.negative = b1.negative;
	
	for( unsigned long i=0 ; i < b.bn_length ; i++){
		b.digits[i] = aux_digits[i];
	}

	delete[] aux_digits;
	aux_digits = NULL;
	
	return b;
	
}

const bignum Karatsuba_multiply::bn_mult_pow10(const bignum & b1, unsigned long n){
	
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

const bignum Karatsuba_multiply::_bn_mult_kara_base_(const bignum& b1_, const bignum& b2_){
	

	bignum zero = 0;
	zero.strategy_ptr = b1_.strategy_ptr;
	bignum b3;
	b3.strategy_ptr = b1_.strategy_ptr;
	bignum b1;
	bignum b2;
    //std::cout <<";karat_base->b1_="<<b1_<<";b2_="<<b2_;
	if( (b1_.digits == NULL) || (b2_.digits == NULL) ){
		return b3;
	}
	
	if( (b1==zero) || (b2==zero) ){
		return zero;
	}
	
	//Se pone en b1 el de mayor cantidad de digitos, y a b2 el que tiene solo un digito
	
	if( b1_.bn_length == 1 ){
		b2 = b1_;
		b1 = b2_;
	}
	else if( b2_.bn_length == 1 ){
		b2 = b2_;
		b1 = b1_;
	}
	else{	
		//std::cout <<";karat_badlength->b1_="<<b1_<<";b2_="<<b2_;
		return b3;
	}
	
	unsigned short carry = 0;	//carry del producto de cada digito
	int base = 10;
	unsigned long aux_length = b1.bn_length + 1;
	unsigned short* aux_digits = new unsigned short[ aux_length ];
	
	for( unsigned long i = 0 ; i < aux_length ; i++ ){
		
		aux_digits[i] = 0;
		
	}
	
	for(unsigned long i = 0; i < b1.bn_length ; i++){
		
		aux_digits[i] = carry + (b1.digits[i] * b2.digits[0]);	
		carry = aux_digits[i] / base;
		aux_digits[i] = aux_digits[i] % base;
		
	}
	
	aux_digits[ aux_length-1 ] = carry;
	
	for( unsigned long i = 0 ; i < aux_length ; i++ ){
		
		if( aux_digits[aux_length-i-1] !=0 ){
			b3.bn_length = aux_length-i;
			break;
		}
		
	}

	b3.digits = new unsigned short[b3.bn_length];
	
	for( unsigned long i=0 ; i < b3.bn_length ; i++){
		b3.digits[i] = aux_digits[i];
	}
	
	if( ( b1.negative && !b2.negative) || (!b1.negative && b2.negative) ){
		b3.negative = true;
	}
	else{
		b3.negative = false;
	}
	
	delete[] aux_digits;
	aux_digits = NULL;
	
	//std::cout <<";result="<<b3<<";";
	return b3;
	
}



const bignum Karatsuba_multiply::multiply_strat(const bignum& a_, const bignum& b_)
{	
	
	bignum result;
    result.strategy_ptr = a_.strategy_ptr;
	bignum zero = 0;
    zero.strategy_ptr = a_.strategy_ptr;
        
	if( (a_.digits == NULL) || (b_.digits == NULL) ){
		return result;
	}
	
	if( (a_==zero) || (b_==zero) ){
		return zero;
	}
	
    unsigned long int k;
	
	bignum a = a_;
	a.negative = false;
	bignum b = b_;
	b.negative = false;
	
	bignum a_0;
    a_0.strategy_ptr = a_.strategy_ptr;
	bignum a_1;
    a_1.strategy_ptr = a_.strategy_ptr;
	bignum b_0;
    b_0.strategy_ptr = a_.strategy_ptr;
	bignum b_1;
    b_1.strategy_ptr = a_.strategy_ptr;
	bignum z0;
    z0.strategy_ptr = a_.strategy_ptr;
	bignum z2;
    z2.strategy_ptr = a_.strategy_ptr;
	bignum z1;
    z1.strategy_ptr = a_.strategy_ptr;

	unsigned long int min_length = min_size(a,b);
	
    if( min_length < 2 ){
		result = _bn_mult_kara_base_(a,b);
	}
    else
    { 
		k = min_length/2 + min_length%2;
		
		a_0 = bn_last_digits(a , a.bn_length-k);
		a_1 = bn_first_digits(a , k );
		b_0 = bn_last_digits( b , b.bn_length-k );
		b_1 = bn_first_digits( b , k );
		z0 = multiply_strat( a_1 , b_1 );
		z2 = multiply_strat( a_0 , b_0 );
		// a_0 += a_1;
		// b_0 += b_1;
		//z1 = multiply_strat( a_0  , b_0 ) - z2 - z0;
		
		z1 = multiply_strat( a_1 + a_0 , b_0 + b_1 ) - z2 - z0;
		
		
		result = z0 + bn_mult_pow10( z1 , k ) + bn_mult_pow10( z2 , 2*k);
		
    }
	
	if( (a_.negative && !b_.negative) || (!a_.negative && b_.negative) ){
		result.negative = true;
	}
	else{
		result.negative = false;
	}
	
    return result;
	
}