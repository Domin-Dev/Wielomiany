#include <iostream>
#include "Wielomian.h"
#include <stdio.h>

using namespace std;

int main()
{
	/*Wielomian w1("3x^3-5x^2-2x");
	Wielomian w2("x^2-2x");*/

	Jednomian j1(10, 2);
	Jednomian j2(8, 0);
	j1.Pokaz();
	printf("\n");
	j2.Pokaz();
	printf("\n%lf", j2[0]);
}

// .../~kg/zajecia/PO1