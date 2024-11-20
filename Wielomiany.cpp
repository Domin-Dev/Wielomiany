#include <iostream>
#include "Wielomian.h"

int main()
{
	Wielomian w1("3x^3-5x^2-2x");
	Wielomian w2("x^2-2x");
	w1.Pokaz();
	Wielomian w3 = w1 / w2;

	w3.Pokaz();
	//w3.~Wielomian();
}


// .../~kg/zajecia/PO1