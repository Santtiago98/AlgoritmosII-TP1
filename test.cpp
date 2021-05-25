#include <iostream>
#include <string>
#include "bignum.h"

//se compila con la siguiente linea:
//g++ -o test test.cpp bignum.cc -Wall -g

using namespace std;

int main(){
	
	//std::string s("9999");
	//std::string s2("25");

	int a = -13;
	int b = 24;

	string s1("2as22");
	string s2("-9331324");

	bignum b1(s1, 30);
	bignum b2(s2, 3);
	bignum c("-12asdas56",5);
	bignum bint(23554,5);
	
	cout << "bint = " << bint << endl;
	cout << "bint precision " << bint.prec() << endl;
	cout << "bint eff size = " << bint.eff_size() << endl;
	
	cout << "c is bad? " << c.bad() << endl;
	
	cout << "c = " << c << "eff y prec:" << c.eff_size() << c.prec() << endl;
	cout << "b1 = " << b1 << "; b2 = " << b2 << endl;
	b1 += b2;
	
	cout << "b1 += b2: " << b1 << endl;
	
	cout << "b1 = " << b1 << "; b2 = " << b2 << endl;
	b1 -= b2;
	cout << "b1 -= b2: " << b1 << endl;
	
	cout << "b1 = " << b1 << "; b2 = " << b2 << endl;
	b1 *= b2;
	cout << "b1 *= b2: " << b1 << endl;
	
	cout << "b1 = " << b1 << "; b2 = " << 11 << endl;
	b1 += 11;
	cout << "b1 += 11: " << b1 << endl;
	
	cout << "b1 = " << b1 << "; b2 = " << 10 << endl;
	b1 *= 10;
	cout << "b1 *= 10: " << b1 << endl;


	//bignum b2(s,4);
	//bignum b2_(s2,4);
	//cout << "hola mundo" << endl;



	
	cout << a << "x" << b << "=" << a*b << endl;
	cout << b1 << "x" << b2 << "=" << b1*b2  << endl;
	

	cin >> b1 ;
	
	if ( b1.bad() ){
		
		cout << "b1 is bad" << endl;
		return 1;
		
	}
	
	cout << b1 << endl;

	// cout << "b = " << b << endl;
	// cout << "b1 = " << b1 << endl;
	// cout << "-b1 = " <<  -b1 << endl;
	// cout << "b2 = " << b2 << endl;
	// cout << "b2_ = " << b2_ << endl;
	
	// cout << b2 << "+" << b2_ << "=" << b2 + b2_ << endl;
	// cout << b2 << "-" << b2_ << "=" << b2 - b2_ << endl;
	
	// cout << -b2 << "+" << b2_ << "=" << -b2 + b2_ << endl;
	// cout << b2_ << "-" << b2 << "=" << b2_ - b2 << endl;
	
	// cout << b2 << "+" << -b2_ << "=" << b2 + (-b2_) << endl;
	// cout << b2_ << "-" << -b2 << "=" << b2_ - (-b2) << endl;
	// cout << -b2_ << "-" << b2 << "=" << -b2_ - b2 << endl;
	// cout << -b2 << "-" << b2_ << "=" << -b2 - b2_ << endl;
	
	// cout << b2 << "<" << b2_ << "=" << (b2 < b2_) << endl;
	// cout << b2 << ">" << b2_ << "=" << (b2 > b2_) << endl;
	// cout << b2 << "==" << b2_ << "=" << (b2 == b2_) << endl;
	// cout << b2 << "==" << b2 << "=" << (b2 == b2) << endl;
	
	// bignum b30;
	
	// cout << "b2_ = " << b2_ << endl << "b1 = " << b1 << endl ;
	
	// b30 = b2_ + b1;
	
	// cout << "hice la suma" << endl;
	//b30 = b1+b2;
	// cout << "b30 = b2_ + b1" << endl;
	// cout << "b30 = " << b30 << endl;
	
	// cout << b30 << "+" << b2 << "=" << b30 + b2 << endl;
	
	// b30 = b30 + b2;
	
	// cout << "b30 = " << b30 << endl;
	
	// bignum b_int = 2147483647;
	// bignum b_int2 = 2147483647;
	
	// cout << "b_int = " << b_int << endl;
	// cout << "b_int2 = " << b_int2 << endl;
	
	// cout << "b_int + b_int2 = " << b_int+b_int2 << endl;
	// cout << "en realidad es = " << 2147483647+2147483647 << endl;
	// cout << "b_int precision = " << b_int.prec() << endl;
	// cout << "b_int effective size = " << b_int.eff_size() << endl;
	
	//cout << bignum("34364678",12) << endl;
	//cout << -bignum("34364678",12) << endl;
	
	// std::string s_("-12345");
	
	// bignum b3(s_,3);
	
	// cout << b3 << endl;
	
	// cout << -b3 << endl;
	
	// std::string s1("-123123asd12345");
	
	// bignum b4(s1,30);
	
	// cout << b4 << endl;
	
	// cout << -b4 << endl;
	
	// cout << "s_: " << s_ << endl;
	
	// cout << "s: " << s << endl;


}