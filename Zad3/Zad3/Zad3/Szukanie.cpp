#include <vector>
#include "Bloczki.h"
#include "Szukanie.h"
#include <iostream>

using namespace std;






void SzukajWGlab(Drzewo drzwo)
{
	Drzewo wynik = 0;
	int k = INT_MAX;
	SzukajWGlab(drzwo, 0, k, wynik);

	cout << "Minimum solution length = " << k << endl;
	if (k == INT_MAX)
	{
		cout << "Brak rozwiazania " << endl;
	}
	else
	{
		while (wynik != 0)
		{
			(wynik)->plansza->wyswietlPlansze();
			wynik = wynik->rodzic;
		}
	}
}

void SzukajWGlab(Drzewo drzwo, int liczbaRuchow, int & minimalna, Drzewo & wynik)
{
	cout << liczbaRuchow << endl;
	if (drzwo->plansza->wygrana())
	{
		if (liczbaRuchow < minimalna)
		{
			minimalna = liczbaRuchow;
			wynik = drzwo;
		}
	}
	if (liczbaRuchow >= minimalna || liczbaRuchow > 9 || !drzwo->plansza->moznaUkonczyc()) return;
	vector<Ruch> mozliweRuchy = drzwo->plansza->pobierzRuchy();
	int i = 0;
	drzwo->dzieci = new ElementDrzewa*[mozliweRuchy.size()];
	drzwo->liczbaDzieci = mozliweRuchy.size();
	for (Ruch r : mozliweRuchy)
	{
		dodajDziecko(drzwo, r,i);
		i++;
	}
	
	for (size_t i = 0; i < drzwo->liczbaDzieci; i++)
	{
		SzukajWGlab(drzwo->dzieci[i], liczbaRuchow + 1, minimalna, wynik);
		if (liczbaRuchow + 1 >= minimalna || liczbaRuchow + 1 > 9) return;
	}
}

void dodajDziecko(Drzewo drzwo, Ruch ruch,int index)
{
	ElementDrzewa* dziecko = new ElementDrzewa();
	dziecko->plansza = new Plansza(*drzwo->plansza);
	dziecko->ruch = new Ruch(ruch);  
	dziecko->plansza->wykonajRuch(ruch);
	dziecko->rodzic = drzwo;
	drzwo->dzieci[index] = dziecko;
}