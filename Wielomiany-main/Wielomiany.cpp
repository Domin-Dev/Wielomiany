#include <iostream>
#include "Wielomian.h"
#include <stdio.h>

using namespace std;

int main()
{
	Wielomian w1("3x^3-5x^2-2x");
	Wielomian w2("x^2-2x");


	Wielomian w3 = w1 % w2;
	w3.Pokaz();
}


// .../~kg/zajecia/PO1