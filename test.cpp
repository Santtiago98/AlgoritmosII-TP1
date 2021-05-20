#include <iostream>
#include <string>
#include "bignum.h"

//se compila con la siguiente linea:
//g++ -o test test.cpp bignum.cc -Wall -g

using namespace std;

int main(){
	
	std::string s("-1004353453454448756756867980713123100");
	std::string s2("943264565475675675675679");
	
	bignum b;
	bignum b1(11);
	bignum b2(s,50);
	bignum b2_(s2,50);
	//cout << "hola mundo" << endl;
	
	cout << b << endl;
	cout << b1 << endl;
	cout << -b1 << endl;
	cout << b2 << endl;
	
	cout << b2 << "+" << b2_ << "=" << b2 + b2_ << endl;
	cout << b2 << "-" << b2_ << "=" << b2 - b2_ << endl;
	
	cout << -b2 << "+" << b2_ << "=" << -b2 + b2_ << endl;
	cout << b2_ << "-" << b2 << "=" << b2_ - b2 << endl;
	
	cout << b2 << "+" << -b2_ << "=" << b2 + (-b2_) << endl;
	cout << b2_ << "-" << -b2 << "=" << b2_ - (-b2) << endl;
	
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