#include "karatsuba.h"
   
const bignum Karatsuba_multiply::bn_last_digits(const bignum & b1, unsigned long int n){
	
	bignum b;
	b.strategy_ptr = b1.strategy_ptr;
    
	if( (b1.digits == NULL) || ( n > b1.bn_length ) ){
		return b;
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
	
	if( (b1.digits == NULL) | ( n > b1.bn_length ) ){
		return b;
	}
	
	b.bn_length = n;
	b.digits = new unsigned short[b.bn_length];
	b.negative = b1.negative;
	
	for( unsigned long i=0 ; i < n ; i++ ){
		b.digits[i] = b1.digits[i];
	}

	return b;
	
}

const bignum Karatsuba_multiply::bn_mult_pow10(const bignum & b1, unsigned long n){
	
	bignum b;
	b.strategy_ptr = b1.strategy_ptr;
    
	if( b1.digits == NULL ){
        return b;
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

const bignum Karatsuba_multiply::_bn_mult_kara_base_(const bignum& b1, const bignum& b2){
	
	unsigned short carry = 0;	//carry del producto de cada digito
	int base = 10;
	bignum b_0 = 0;
	bignum b3;
	b3.strategy_ptr = b1.strategy_ptr;
    
	if( (b1.digits == NULL) || (b2.digits == NULL) ){
		return b3;
		
	}
	
	if( (b1==b_0) || (b2==b_0) ){
		
		return b_0;
		
	}
	
	unsigned long aux_length = b1.bn_length + b2.bn_length + 1;
	unsigned short* aux_digits = new unsigned short[ aux_length ];
	
	for( unsigned long i = 0 ; i < aux_length ; i++ ){
		
		aux_digits[i] = 0;
		
	}
	
	for(unsigned long i = 0; i < b2.bn_length ; i++){
		
		carry = 0;
		for(unsigned long j = 0 ; j < b1.bn_length ; j++){
			
			aux_digits[i+j] += carry + b1.digits[j] * b2.digits[i];	
			carry = aux_digits[i+j] / base;
			aux_digits[i+j] = aux_digits[i+j] % base;
			
		}

		if( carry != 0 ) {
			
			aux_digits[ i + b1.bn_length ] = carry;
			
		}
		
	}
	
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
	
    if( min_length < 10 ){
		result = _bn_mult_kara_base_(a,b);
	}
    else
    { 
		k = min_length/2;
		
		a_0 = bn_last_digits(a , a.bn_length-k);
		a_1 = bn_first_digits(a , k );
		b_0 = bn_last_digits( b , b.bn_length-k );
		b_1 = bn_first_digits( b , k );

		z0 = multiply_strat( a_1 , b_1 );
		z2 = multiply_strat( a_0 , b_0 );
		z1 = multiply_strat( a_0 + a_1 , b_0 + b_1 ) - z2 - z0;
		
		result = z0 + bn_mult_pow10( z1 , k ) + bn_mult_pow10( z2 , 2*k );
		
    }
	
	if( (a_.negative && !b_.negative) || (!a_.negative && b_.negative) ){
		result.negative = true;
	}
	else{
		result.negative = false;
	}
	
    return result;
	
}