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
	w1 /= w2;

	cout << w1.Pokaz() << endl;
}

