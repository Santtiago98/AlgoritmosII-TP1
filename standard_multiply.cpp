#include "standard_multiply.h"


const bignum Standard_multiply::multiply_strat(const bignum& b1, const bignum& b2){
	

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
	
	//cout << "debug print, digitos pedidos = " << b1.bn_length + b2.bn_length + 1 << endl;
	unsigned long aux_length = b1.bn_length + b2.bn_length + 1;
	unsigned short* aux_digits = new unsigned short[ aux_length ];
	
	
	for( unsigned long i = 0 ; i < aux_length ; i++ ){
		
		aux_digits[i] = 0;
		
	}
	
	// El producto b1[1..p] y b2[1..q] tiene largo p+q[-1] dependiendo del carry final
	
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
	
	//delete [] b3.digits;
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
	
	//cout << "="<<b3;
	return b3;
	
}

