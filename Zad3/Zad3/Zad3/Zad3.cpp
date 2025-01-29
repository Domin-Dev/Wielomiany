#include <stdio.h>
#include <string>
#include <stdlib.h>
#include <iostream>
#include <fstream>


using namespace std;

void pobierzRozmiar(char* fileName, int* szerokosc, int* wysokosc);

class Plansza
{
	char** bloczki;
	 
	Plansza(int szerokosc, int wysokosc)
	{
		bloczki = new char[szerokosc][wysokosc];
	}

	void DodajBloczek(int x,int y,char bloczek)
	{

	}
};

//
//
//class Bloczek
//{
//	char znak;
//
//	Bloczek(char znak)
//	{
//		this->znak = znak;
//	}
//};


void wczytajPlansze()
{
	string str;
	cout << "Podaj nazwe pliku do odczytu:";
	cin >> str;
	int szer, wysok;
	pobierzRozmiar((char*)str.c_str(), &szer, &wysok);

	cout << szer << "  " << wysok;
	ifstream file(str.c_str());
	if (!file.is_open()) return;
	string x;
	Plansza plansza = new Plansza(szer, wysok);

	while (file >> x) 
	{
		for (size_t i = 0; i < x.length(); i++)
		{
		   char c = x.at(i);
		   switch ( c)
		   {
		   case '#':

			   break;
		   case '-':

			   break;
		   default:
			   break;
		   }
		   cout << c << " ";
		}
		cout << endl;
	}
	file.close();
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
	wczytajPlansze();
}