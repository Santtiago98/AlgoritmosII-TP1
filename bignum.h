#include <iostream>

class bignum
{
private:
unsigned short *digits;
// ...INCOMPLETO --> AGREGAR LO QUE SEA NECESARIO 

public:
// ...INCOMPLETO --> AGREGAR LO QUE SEA NECESARIO 

friend bignum operator+(const bignum&, const bignum&);
friend bignum operator-(const bignum&, const bignum&);
friend bignum operator*(const bignum&, const bignum&);
friend std::ostream& operator<<(std::ostream&, const bignum&);
friend std::istream& operator>>(std::istream&, bignum&);
};