#ifndef __STANDARD_H_INCLUDED__
#define __STANDARD_H_INCLUDED__

#include <iostream>
#include "bignum.h"
#include "strategy.h"

class Standard_multiply : public Strategy{
    public:
        const bignum multiply_strat(const bignum& b1, const bignum& b2);
};

#endif
