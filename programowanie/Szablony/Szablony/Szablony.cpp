

#include <iostream>
#include <vector>

using namespace std;


int NWD(int a, int b)
{
	while (a != b)
		if (a > b)
			a -= b;
		else
			b -= a; 
	return a; 
}
class Ulamek 
{
	double licznik;
	double mianownik;

	public:
		Ulamek(double licznik, double mianownik);
		Ulamek(int licznik);
		Ulamek& operator=(const int& d);
		Ulamek& operator+=(const Ulamek& u);
		friend std::ostream& operator<<(std::ostream& os, const Ulamek& u);
};
Ulamek::Ulamek(double licznik, double mianownik)
{
	this->licznik = licznik;
	this->mianownik = mianownik;
}
Ulamek::Ulamek(int licznik)
{
	this->licznik = licznik;
	this->mianownik = 1;
}
Ulamek& Ulamek::operator=(const int& d)
{
	this->licznik = d;
	this->mianownik = mianownik;
	return *this;
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
	int nwd = NWD(mianownik, licznik);
	mianownik /= nwd;
	licznik /= nwd;

	return *this;
	}
std::ostream& operator<<(std::ostream& os, const Ulamek& u)
{
	if (u.mianownik == 1)
		os << u.licznik;
	else
		os << u.licznik << "/" << u.mianownik;
	return os;
}
double suma(double * tab, int liczba)
{
	double suma = 0;
	for (size_t i = 0; i < liczba; i++)
	{
		suma += tab[i];
	}
	return suma;
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

int podzielnePrzez3(int wartosc)
{
	return wartosc % 3 == 0;
}

int ileSpelnia(int* tab, int rozmiar)
{
	int liczba = 0;
	for (size_t i = 0; i < rozmiar; i++)
		if(podzielnePrzez3(tab[i])) liczba++;
	return liczba;
}
template<typename T,typename F>
int ileSpelnia(T tab,int rozmiar, F kryterium)
{
	int liczba = 0;
	for (size_t i = 0; i < rozmiar; i++)
		if (kryterium(tab[i])) liczba++;
	return liczba;
}

template<typename T, typename F>
int ileSpelnia(T tab, int rozmiar, int (*kryterium) (F))
{
	int liczba = 0;
	for (size_t i = 0; i < rozmiar; i++)
		if (kryterium(tab[i])) liczba++;
	return liczba;
}

class WiekszeOd30
{
	public:
		template<typename T>
		int operator()(T wartosc)
		{
			return wartosc > 30;
		}
};

int main()
{
	int tab[] = { 12,3,13,11,124,24,35,3};
	vector<int> v = { 12,3,13,2,124,324,5,7 };
	vector<Ulamek> vu;

	vu.push_back(Ulamek(3, 3));
	vu.push_back(Ulamek(7, 3));
	vu.push_back(Ulamek(2, 2));

	WiekszeOd30 wiekszeOd30;

	std::cout << suma<vector<int>, int>(v, 8) << endl;
	std::cout << suma<vector<Ulamek>, Ulamek>(vu, 3) << endl;
	cout << endl;
	std::cout << ileSpelnia<vector<int>, int>(v, 8, podzielnePrzez3) << endl;
	std::cout << ileSpelnia<vector<int>, WiekszeOd30>(v,8,wiekszeOd30)<< endl;
}