#include <iostream>
#include "Wielomian.h"

int main()
{
	Wielomian w1("5x^3-2x^2+1x-4");
	Wielomian w2("x^2-3");

	Wielomian w5("x^2");
	Wielomian w6("x^2");


	Wielomian w3 = w1 - w2;

	w3.Pokaz();
	printf("%lf", w3[0]);

}


// .../~kg/zajecia/PO1