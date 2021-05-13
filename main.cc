#include <iostream>
#include <sstream>
#include "bignum.h"
using namespace std;

int main(int argc, char ** argv){
	 
	 int precision; 
	 
	 for(int i=0; i<argc; i++)
	 {
	 	if(*argv[i] == '-'){
	 		switch(*(argv[i]+1)){
	 			case 'p':{
	 				stringstream ss(argv[i+1]);
	 				ss >> precision ;
	 				cout<<"Se seteó una precisión de: "<< precision <<endl;
	 				break;
	 			}
	 			case 'i':
	 				//setear input stream
	 				break;
	 			case 'o':
	 				//setear output stream
	 				break;
	 			default:
	 				//Manecout<<"hola"<<endl;
	 				break;

	 		}
	 	}
	 	
	 }


	
	 return 0;

}
