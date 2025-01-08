#include <iostream>
#include "Wielomian.h"
#include <stdio.h>

using namespace std;

int main()
{
	Wielomian w1("3x^3-5x^2-2x");
	Wielomian w2("x^2-2x");
	
	Jednomian j1(10, 2);
	Jednomian j2(10,3);

	cout << w1.Pokaz() << endl;
	Wielomian w3 = j1 + j2;

	cout << w3.Pokaz() << endl;
}

