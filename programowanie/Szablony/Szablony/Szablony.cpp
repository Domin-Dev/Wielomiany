

#include <iostream>
#include <vector>

using namespace std;


class Ulamek 
{
	double licznik;
	double mianownik;

	public:
		Ulamek(double licznik, double mianownik);
		Ulamek& operator=(const double& d);
		Ulamek& operator+=(const Ulamek& u);
};

Ulamek::Ulamek(double licznik, double mianownik)
{
	this->licznik = licznik;
	this->mianownik = mianownik;
}

Ulamek& Ulamek::operator=(const double& d)
{
	licznik = d;
	mianownik = 1;
}

Ulamek& Ulamek::operator+=(const Ulamek& u)
{
	if (mianownik == u.mianownik)
	{
		licznik += u.licznik;
	}
	else
	{
		licznik = licznik * u.mianownik + u.licznik * mianownik;
		mianownik *= u.mianownik;
	}
}




template <typename T>
T suma(T tab, int liczba)
{
	T suma = 0;
	for (size_t i = 0; i < liczba; i++)
	{
		suma += tab[i];
	}
	return suma;
}

template <typename K, typename T>
T suma(K k, int liczba)
{
	T suma = 0;
	for (size_t i = 0; i < liczba; i++)
	{
		suma += k[i];
	}
	return suma;
}

int czyParzysta(int wartosc)
{
	return wartosc % 2 == 0;
}


template<typename T,typename F>
int sprawdz(T* tab,int rozmiar, F kryterium)
{
	int liczba = 0;
	for (size_t i = 0; i < rozmiar; i++)
		if (kryterium(tab[i])) liczba++;
	return liczba;
}

int main()
{
	int tab[] = { 12,3,13,42,124,24,35 };
	vector<int> v = { 12,3,13,42,124,24,35 };

	std::cout << suma(tab, 7) << endl;
	std::cout << suma<vector<int>,int>(v, 7) << endl;
	std::cout << sprawdz(v,7,czyParzysta) << endl;
}