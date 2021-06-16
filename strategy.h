#ifndef __STRATEGY_H_INCLUDED__
#define __STRATEGY_H_INCLUDED__

#include <iostream>
#include "bignum.h"

class Strategy {
    public:
        virtual ~Strategy(){};
        virtual const bignum multiply_strat(const bignum &, const bignum &)  = 0;
};

#endif
