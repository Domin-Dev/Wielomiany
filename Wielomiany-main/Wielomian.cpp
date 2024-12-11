#include "Wielomian.h"
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string>

using namespace std;

char* BezSpacji(const char* napis);
int WyznaczStopien(const char* napis);


////// ////////// //////
///// /Jednomian ///////
//// ////////// ////////

Jednomian::Jednomian(double wartosc, int stopien)
{
	this->wartosc = wartosc;
	this->stopien = stopien;        
}

double Jednomian::operator[](int index)
{
	return wartosc;
}

void Jednomian::Pokaz()
{
	if (wartosc == 0)
	{
		printf("0");
	}
	else
	{
		if (stopien > 0)
		{
			printf("%.3lfx^%d",wartosc,stopien);
		}
		else
		{
			printf("%.3lf", wartosc, stopien);
		}
	}
}

//////////////////////
//////////////////////

Wielomian::Wielomian(const char* napis)
{
	wsp = 0;
	Analizuj(napis);
}

Wielomian::Wielomian(int stopien)
{
	InicjujWielomian(stopien);
}

Wielomian::Wielomian()
{
	InicjujWielomian(0);
}

Wielomian::Wielomian(const Wielomian& w)
{
	this->stopien = w.stopien;
	wsp = new double[stopien + 1]();
	for (size_t i = 0; i <= stopien; i++)
	{
		wsp[i] = w.wsp[i];
	}
}

Wielomian::Wielomian(int stopien, double* wsp)
{
	InicjujWielomian(stopien);
	for (size_t i = 0; i <= stopien; i++)
	{
		this->wsp[i] = wsp[i];
	}
}

void Wielomian::InicjujWielomian(int stopien)
{
	this->stopien = stopien;
	this->wsp = new double[stopien + 1]();
}

double Wielomian::operator[](int index)
{
	return wsp[index];
}

void Wielomian::Analizuj(const char* napis)
{
	const char* bezspacji = BezSpacji(napis);
	napis = bezspacji;
	int stopien = WyznaczStopien(napis);
	InicjujWielomian(stopien);
	while (*napis)
		napis = AnalizujJednomian(napis);
	delete[] bezspacji;
}

char* BezSpacji(const char* napis)
{
	int i = 0;
	const char* p = napis;
	while (*p)
	{
		if (*p++ != ' ')i++;
	}
	char* bezspacji = new char[i+1];
	i = 0;
	p = napis;
	while(*p)
	{
		if (*p != ' ')
		{
			bezspacji[i++] = *p;
		}
		p++;
	}
	bezspacji[i] = 0;
	return bezspacji;
}

int WyznaczStopien(const char* napis)
{
	int maxStopien = 0;
	while(*napis)
	{
		if (*napis == 'x')
		{
			int stopien = 1;
			napis++;
			if(*napis == '^')
			{
				char* koniec;
				stopien = strtol(++napis,&koniec, 10);
				napis = koniec;
			}
			if (stopien > maxStopien)
			{
				maxStopien = stopien;
			}
		}
		napis++;
	}
	return maxStopien;
}

char* Wielomian::AnalizujJednomian(const char* napis)
{
	bool minus = false;
	int stopien = 0;
	char* koniec;
	if (napis[0] == '-')
	{
		minus = true;
		napis++;
	}
	else if (napis[0] == '+')
	{
		napis++;
	}
	double wartosc = 1;
	if (*napis != 'x') {
		wartosc = strtod(napis, &koniec);
		napis = koniec;
	}

	if (*napis == 'x')
	{
		stopien = 1;
		napis++;
		if (*napis == '^')
		{
			stopien = strtol(++napis, &koniec, 10);
			napis = koniec;
		}
	}

	if (minus) wartosc = -wartosc;
	wsp[stopien] += wartosc;
	return (char*)napis;
}



void Wielomian::Pokaz()
{
	printf("\n[");
	for (int i = stopien; i >= 0; i--)
	{
		if (wsp[i] != 0)
		{
			if (i == 0)
			{
				printf(" %.4lf ", wsp[i]);
			}
			else
			{
				printf(" %.4lfx^%d ", wsp[i],i);
			}
		}
	}
	printf("]");
}


//
//
//void Wielomian::Powieksz(int stopien)
//{
//	double* tab = new double[stopien + 1]();
//	for (int i = 0; i <= this->stopien; i++)
//		tab[i] = wsp[i];
//
//	delete[]wsp;
//	wsp = tab;
//	this->stopien = stopien;
//}
//
//void Wielomian::WeryfikujStopien()
//{
//	while(stopien > 0 && wsp[stopien] == 0)
//		stopien--;
//}
//
//
//Wielomian& Wielomian::Dzielenie(const Wielomian& w1, Wielomian& reszta)
//{
//	if (w1.stopien > stopien)
//	{
//		reszta = *this;
//		Wielomian z(0);
//		*this = z;
//		return *this;
//	}
//	Wielomian wynik(this->stopien - w1.stopien);
//	Wielomian w = *this;
//	while (true)
//	{
//		double x = w.wsp[w.stopien] / w1.wsp[w1.stopien];
//		int st = w.stopien - w1.stopien;	
//		Jednomian nowy(st, x);
//		wynik.wsp[st] = x;
//		Wielomian w2 = w1  * nowy;
//		w2 *= -1.0;
//		w += w2;
//		if (w.stopien == 0)
//		{
//			wynik.WeryfikujStopien();
//			reszta = NULL;
//			*this = wynik;
//			return *this;
//		}
//		else if (w.stopien < w1.stopien)
//		{
//			wynik.WeryfikujStopien();
//
//			reszta = w;
//			*this = wynik;
//			return  *this;
//		}
//	}
//	return *this;
//}
//
//Wielomian Wielomian::Pochodna()
//{
//	if (stopien <= 0) return NULL;
//	Wielomian w1 (stopien - 1);
//	for (size_t i = 0; i <= stopien; i++)
//	{
//		if (i == 0) w1.wsp[i] = 0;
//		else
//		{
//			w1.wsp[i - 1] = wsp[i] * i;
//		}
//	}
//	return w1;
//}
//
//Wielomian& Wielomian::operator+=(const Wielomian& w1)
//{
//	if (w1.stopien > stopien)
//		Powieksz(w1.stopien);
//	for (int i = 0; i <= w1.stopien; i++)
//	{
//		wsp[i] += w1.wsp[i];
//	}
//	WeryfikujStopien();
//	return *this;
//}
//
//Wielomian& Wielomian::operator+=(const double& d) 
//{
//	wsp[0] += d;
//	return *this;
//}
//
//Wielomian& Wielomian::operator=(const Wielomian& w1)
//{
//	if (w1.stopien > stopien) Powieksz(w1.stopien);
//	for (size_t i = 0; i <= stopien; i++)
//	{
//		if (i <= w1.stopien)
//			wsp[i] = w1.wsp[i];
//		else
//			wsp[i] = 0;
//	}
//	WeryfikujStopien();
//	return *this;
//}
//
//Wielomian& Wielomian::operator-=(const Wielomian& w1)
//{
//	for (size_t i = 0; i <= w1.stopien; i++)
//	{
//		w1.wsp[i] = -w1.wsp[i];
//	}
//	return *this += w1;
//}
//
//Wielomian& Wielomian::operator-=(const double& d)
//{
//	return operator+=(-d);
//}
//
//Wielomian& Wielomian::operator*=(const Wielomian& w1)
//{
//	Wielomian wynik(w1.stopien + stopien);
//	for (size_t i = 0; i <= stopien; i++)
//	{
//		if (wsp[i] == 0) continue;
//		
//		for (size_t j = 0; j <= w1.stopien; j++)
//		{
//			if (w1.wsp[j] == 0) continue;
//			wynik.wsp[i + j] += wsp[i] * w1.wsp[j];
//		}
//	}
//	Powieksz(wynik.stopien);
//	for (size_t i = 0; i <= wynik.stopien; i++)
//	{
//		wsp[i] = wynik.wsp[i];
//	}
//	return *this;
//}
//
//Wielomian& Wielomian::operator*=(const double& d)
//{
//	for (size_t i = 0; i <= stopien; i++)
//	{
//		if (wsp[i] == 0) continue;
//		wsp[i] *= d;
//	}
//	return *this;
//}
//
//Wielomian& Wielomian::operator/=(const Wielomian& w1)
//{
//	Wielomian w(0);
//	return Dzielenie(w1, w);
//}
//
//Wielomian& Wielomian::operator/=(const double& d)
//{
//	double w[1];
//	w[0] = d;
//	Wielomian w1(0, w);
//	Wielomian w2(0);
//	return Dzielenie(w1, w2);
//}
//
//Wielomian& Wielomian::operator%=(const Wielomian& w1)
//{
//	Wielomian w(0);
//	Dzielenie(w1,w);
//
//	*this = w;
//	return *this;
//}
//
//double Wielomian::operator [](int index)
//{
//	return wsp[index];
//}
//
//double Wielomian::operator()(int index)
//{
//	double wynik = wsp[stopien];
//	for (int i = stopien - 1; i >= 0; i--)
//		wynik = wynik * index + wsp[i];
//	return wynik;
//}
//
//
//
//std::istream& operator>>(std::istream& is, Wielomian& w)
//{
//	string wielomian;
//	cout << "Podaj wielomian:";
//	is >> wielomian;
//	w = Wielomian(wielomian.c_str());
//	return is;
//}
//
//std::ostream& operator<<(std::ostream& os, const Wielomian& w)
//{	
//	os << "\n";
//	for (int i = w.stopien; i >= 0; i--)
//	{
//		if (w.wsp[i] != 0)
//		{
//			if (i == 0)
//			{
//				if (w.wsp[i] > 0) os << "+" << w.wsp[i];
//				else os << w.wsp[i];
//			}
//			else
//			{
//				if(w.wsp[i] > 0) os << "+" << w.wsp[i] << "x^" << i;
//				else os << w.wsp[i] << "x^" << i;
//			}
//		}
//	}
//	return os;
//}
//
//Wielomian operator+(const Wielomian& w1, const Wielomian& w2)
//{
//	Wielomian wynik = w1;
//	wynik+=w2;
//	return wynik;
//}
//
//Wielomian operator+(const Wielomian& w1, const double& d)
//{
//	Wielomian wynik = w1;
//	wynik += d;
//	return wynik;
//}
//
//Wielomian operator+(const double& d, const Wielomian& w1)
//{
//	return (operator+(w1, d));
//}
//
//
//Wielomian operator-(const Wielomian& w1, const Wielomian& w2)
//{
//	Wielomian wynik = w1;
//	wynik -= w2;
//	return wynik;
//}
//
//Wielomian operator-(const Wielomian& w1, const double& d)
//{	
//	Wielomian wynik = w1;
//	wynik -= d;
//	return wynik;
//}
//
//Wielomian operator-(const double& d, const Wielomian& w1)
//{
//	Wielomian wynik = w1;
//	for (size_t i = 0; i <= wynik.stopien; i++)
//	{
//		wynik.wsp[i] = -wynik.wsp[i];
//	}
//	wynik.wsp[0] += d;
//	return wynik;
//}
//
//
//Wielomian operator/(const Wielomian& w1, const Wielomian& w2)
//{
//	Wielomian wynik = w1;
//	wynik /= w2;
//	return wynik;
//}
//
//Wielomian operator/(const double& d, const Wielomian& w1)
//{
//	double* wsp = new double[1];
//	wsp[0] = d;
//	Wielomian wynik(0, wsp);
//	wynik /= w1;
//	return wynik;
//}
//
//Wielomian operator/(const Wielomian& w1, const double& d)
//{
//	Wielomian wynik = w1;
//	for (size_t i = 0; i < wynik.stopien; i++)
//	{
//		wynik.wsp[i] /= d;
//	}
//	return wynik;
//}
//
//Wielomian operator*(const Wielomian& w1, const Wielomian& w2)
//{
//	
//	Wielomian wynik = w1;
//	wynik *= w2;
//	return wynik;
//}
//
//Wielomian operator*(const Wielomian& w1, const double& d)
//{
//	Wielomian wynik = w1;
//	wynik *= d;
//	return wynik;
//}
//
//Wielomian operator*(const double& d, const Wielomian& w1)
//{
//	Wielomian wynik = w1;
//	wynik *= d;
//	return wynik;
//}
//
//Wielomian operator%(const Wielomian& w1, const Wielomian& w2)
//{
//	Wielomian wynik = w1;
//	wynik %= w2;
//	return wynik;
//}
//
//Wielomian operator%(const Wielomian& w1, const double& d)
//{
//	Wielomian wynik = w1;
//	double* wsp = new double[1];
//	wsp[0] = d;
//	Wielomian w2(0, wsp);
//	wynik %= w2;
//	return wynik;
//}
//
//Wielomian operator%(const double& d, const Wielomian& w1)
//{
//	double* wsp = new double[1];
//	wsp[0] = d;
//	Wielomian wynik(0, wsp);
//	wynik %= w1;
//	return wynik;
//}
//
//Jednomian::Jednomian(int stopien,double wartosc)
//{
//	InicjujWielomian(stopien);
//	wsp[stopien] = wartosc;
//}


