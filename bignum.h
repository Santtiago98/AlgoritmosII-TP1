#include <iostream>

class bignum
{
    private:
        unsigned short *digits;
        unsigned short precision; // prec=4 --> XXXX 
	unsigned short efective_size;
        bool negative;      
    // ...

    public:
    // ...

		~bignum();   //adentro liberar espacio

		bignum(); //prec x defecto - Inicializado en 0
		bignum(const unsigned short precision);     //util para resultado metodos
		bignum(const string &, const unsigned short precision);   //"12315", p>=size(str+sign)
		bignum(const bignum &);  //constr copia

		friend bignum operator+(const bignum&, const bignum&);  //p =pmax{p1,p2} 
		friend bignum operator-(const bignum&, const bignum&);  //p =pmax{p1,p2}
		friend bignum operator*(const bignum&, const bignum&);  //p =pmax{p1,p2}
		friend bignum operator*(const bignum&, const bignum&);  //p =pmax{p1,p2}

		friend bignum const &operator=(const bignum &);

		friend std::ostream& operator<<(std::ostream&, const bignum&);
		friend std::istream& operator>>(std::istream&, bignum&);
}
