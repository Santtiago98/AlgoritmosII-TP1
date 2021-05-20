#include <iostream>
#include <string>
#include "bignum.h"

using namespace std;

int main(){
	
	std::string s("10000");
	std::string s2("99");
	
	bignum b;
	bignum b1(11);
	bignum b2(s,5);
	bignum b2_(s2,30);
	//cout << "hola mundo" << endl;
	
	cout << b << endl;
	cout << b1 << endl;
	cout << -b1 << endl;
	cout << b2 << endl;
	
	cout << b2 << "+" << b2_ << "=" << b2 + b2_ << endl;
	cout << b2 << "-" << b2_ << "=" << b2 - b2_ << endl;
	
	cout << b2 << "<" << b2_ << "=" << (b2 < b2_) << endl;
	cout << b2 << ">" << b2_ << "=" << (b2 > b2_) << endl;
	cout << b2 << "==" << b2_ << "=" << (b2 == b2_) << endl;
	
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