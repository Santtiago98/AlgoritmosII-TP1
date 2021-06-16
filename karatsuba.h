#ifndef __KARATSUBA_H_INCLUDED__
#define __KARATSUBA_H_INCLUDED__

#include <iostream>
#include "strategy.h"
#include "bignum.h"

class Karatsuba_multiply : public Strategy{
    public:
        const bignum multiply_strat(const bignum& b1, const bignum& b2);
    private:
        const bignum bn_last_digits(const bignum &, unsigned long );
        const bignum bn_first_digits(const bignum &, unsigned long );
        const bignum bn_mult_pow10(const bignum &, unsigned long );
        const bignum _bn_mult_kara_base_(const bignum &, const bignum&);
        
};

#endif
