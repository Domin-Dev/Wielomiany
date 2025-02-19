#include <stdio.h>
#include <string>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <vector>
#include "Bloczki.h"
#include "Szukanie.h"

using namespace std;


void pobierzRozmiar(char* fileName, int* szerokosc, int* wysokosc);





Plansza * wczytajPlansze()
{
	string str;
	cout << "Podaj nazwe pliku do odczytu:";
	cin >> str;
	int szer, wysok;
	pobierzRozmiar((char*)str.c_str(), &szer, &wysok);

	cout << "Rozmiar planszy:" << szer << " x " << wysok << endl;
	ifstream file(str.c_str());
	if (!file.is_open()) return new Plansza(0,0);
	Plansza * plansza = new Plansza(szer, wysok);
	plansza->wczytajPlansze(&file);
	plansza->wyswietlPlansze();

	file.close();
	return plansza;
}

void pobierzRozmiar(char * fileName, int * szerokosc, int * wysokosc)
{
	ifstream file(fileName);
	if (!file.is_open()) return;
	string x;
	*szerokosc = *wysokosc = 0;

	while (file >> x)
	{
		*szerokosc = x.length();
		(*wysokosc)++;
	}
	file.close();
}

void main()
{
	Plansza * plansza = wczytajPlansze();
	Drzewo drzwo = (Drzewo)malloc(sizeof(ElementDrzewa));
	plansza->wyswietlPlansze();
	Plansza * k = new Plansza(*plansza);

	ElementDrzewa * el = new ElementDrzewa();
	drzwo->dodajDziecko();

	//drzwo->rodzic = 0;

    SzukajWGlab(drzwo);
}