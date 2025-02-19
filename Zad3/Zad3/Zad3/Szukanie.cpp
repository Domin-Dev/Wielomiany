#include <vector>
#include "Bloczki.h"
#include "Szukanie.h"
#include <iostream>

using namespace std;






void SzukajWGlab(Drzewo drzwo)
{
	Drzewo* wynik = 0;
	SzukajWGlab(drzwo, 0, INT_MAX, wynik);
}

void SzukajWGlab(Drzewo drzwo, int liczbaRuchow, int minimalna, Drzewo* wynik)
{
	if (drzwo->plansza->wygrana())
	{
		if (liczbaRuchow < minimalna)
		{
			minimalna = liczbaRuchow;
			wynik = &drzwo;
		}
	}
	vector<Ruch> mozliweRuchy = drzwo->plansza->pobierzRuchy();
	for (Ruch r : mozliweRuchy)
	{
		dodajDziecko(drzwo, r);
	}
	//for (ElementDrzewa r : drzwo->dzieci)
	//{
	//	SzukajWGlab(&r, liczbaRuchow + 1,minimalna, wynik);
	//	if (liczbaRuchow + 1 >= minimalna) return;
	//}

}

Drzewo dodajDziecko(Drzewo drzwo, Ruch ruch)
{
//	// Sprawdzenie, czy 'drzwo' jest nullptr
//	if (drzwo == nullptr) {
//		cout << " blad!!!!";
//		return nullptr;
//	}
//
//	// Tworzenie nowego dziecka
////	Drzewo dziecko = new ElementDrzewa();  // Przypisanie rodzica
//
//	// Tworzenie kopii planszy i ruchu
//	dziecko->plansza = new Plansza(*drzwo->plansza);
//	dziecko->ruch = new Ruch(ruch);  // Tworzymy kopiê ruchu
//
//	// Wykonanie ruchu na planszy
//	dziecko->plansza->wykonajRuch(ruch);
//
//	// Dodanie nowego dziecka do wektora 'dzieci'
//	drzwo->dzieci.push_back(dziecko);
//
//	// Zwrócenie nowego dziecka
//	return dziecko;
	return nullptr;
}