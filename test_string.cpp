#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

int main(){
	
	
	std::string s_("-12345");
	
	std::string s(s_);
	
	
	
	std::reverse(s.begin() + 1 , s.end());
	
	cout << "s_: " << s_ << endl;
	
	cout << "s len: " << s.length() << endl;
	
	cout << "s: " << s << endl;
	
	cout << s[1] << endl;
	
}