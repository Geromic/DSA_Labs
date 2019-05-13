#include <iostream>
#include "ExtendedTest.h"
#include "ShortTest.h"
using namespace std;

int main(){
	testAll();
	cout << "Short passed!" << endl;
	testAllExtended();
	cout << "Extended passed!" << endl;

	return 0;
}