#include <iostream>
#include "Wielomian.h"

int main()
{
	Wielomian w1("10x^2+3x");
	Wielomian w2("20x^3+10+2+x");
	w1.Pokaz();
	w2.Pokaz();
	w1 *= w2;
	w1.Pokaz();

}


// .../~kg/zajecia/PO1