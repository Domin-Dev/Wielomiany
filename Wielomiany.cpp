#include <iostream>
#include "Wielomian.h"
#include <stdio.h>

using namespace std;

int main()
{ 
	Wielomian w1("5x^3-2x^2+1x-4");
	Wielomian w2("x^2-3");

	Wielomian w5("x^2");
	Wielomian w6("x^2");

	cout << w5 << w1; 
}


// .../~kg/zajecia/PO1