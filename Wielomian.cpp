#include "Wielomian.h"
#include <stdlib.h>
#include <stdio.h>

char* BezSpacji(const char* napis);
int WyznaczStopien(const char* napis);



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

Wielomian::Wielomian(const char* napis)
{
	wsp = 0;
	Analizuj(napis);
}

Wielomian::Wielomian(int stopien)
{
	InicjujWielomian(stopien);
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

void Wielomian::InicjujWielomian(int stopien)
{
	this->stopien = stopien;
	this->wsp = new double[stopien + 1]();
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

void Wielomian::Powieksz(int stopien)
{
	double* tab = new double[stopien + 1]();
	for (int i = 0; i <= this->stopien; i++)
		tab[i] = wsp[i];

	delete[]wsp;
	wsp = tab;
	this->stopien = stopien;
}

void Wielomian::WeryfikujStopien()
{
	while(stopien > 0 && wsp[stopien] == 0)
		stopien--;
}

Wielomian& Wielomian::operator+=(const Wielomian& w1)
{
	if (w1.stopien > stopien)
		Powieksz(w1.stopien);
	for (int i = 0; i <= w1.stopien; i++)
	{
		wsp[i] += w1.wsp[i];
	}
	WeryfikujStopien();
	return *this;
}

Wielomian& Wielomian::operator-=(const Wielomian& w1)
{
	for (size_t i = 0; i <= w1.stopien; i++)
	{
		w1.wsp[i] = -w1.wsp[i];
	}
	return *this += w1;
}

Wielomian& Wielomian::operator*=(const Wielomian& w1)
{
	Wielomian wynik(w1.stopien + stopien);
	for (size_t i = 0; i <= stopien; i++)
	{
		if (wsp[i] == 0) continue;
		
		for (size_t j = 0; j <= w1.stopien; j++)
		{
			if (w1.wsp[j] == 0) continue;
			wynik.wsp[i + j] += wsp[i] * w1.wsp[j];
		}
	}
	Powieksz(wynik.stopien);
	for (size_t i = 0; i <= wynik.stopien; i++)
	{
		wsp[i] = wynik.wsp[i];
	}
	return *this;
}

Wielomian& Wielomian::operator*=(const double& d)
{
	for (size_t i = 0; i <= stopien; i++)
	{
		if (wsp[i] == 0) continue;
		wsp[i] *= d;
	}
	return *this;
}

Wielomian& Wielomian::operator/=(const Wielomian& w1)
{
	if (w1.stopien > stopien) return *this;
	Wielomian wynik(this->stopien - w1.stopien);
	Wielomian w = *this;
	while (true)
	{
		double x = w.wsp[w.stopien] / w1.wsp[w1.stopien];
		int st = w.stopien - w1.stopien;
		Wielomian nowy(st);
		nowy.wsp[st] = x;
		wynik.wsp[st] = x;
		Wielomian w2 = w1 * nowy;
		w2 *= -1.0;
		w += w2;
		if (w.stopien == 0)
		{
			wynik.WeryfikujStopien();
			*this = wynik;
			return *this;
		}
		else if (w.stopien > w1.stopien)
		{
			wynik.WeryfikujStopien();
			return wynik;
		}
	}
	return *this;
}

Wielomian operator+(const Wielomian& w1, const Wielomian& w2)
{
	Wielomian wynik = w1;
	wynik+=w2;
	return wynik;
}

Wielomian operator-(const Wielomian& w1, const Wielomian& w2)
{
	Wielomian wynik = w1;
	wynik -= w2;
	return wynik;
}

Wielomian operator/(const Wielomian& w1, const Wielomian& w2)
{
	Wielomian wynik = w1;
	wynik /= w2;
	wynik.Pokaz();
	return wynik;
}

Wielomian operator*(const Wielomian& w1, const Wielomian& w2)
{
	
	Wielomian wynik = w1;
	wynik *= w2;
	return wynik;
}

Wielomian operator*(const Wielomian& w1, const double& d)
{
	Wielomian wynik = w1;
	wynik *= d;
	return wynik;
}
