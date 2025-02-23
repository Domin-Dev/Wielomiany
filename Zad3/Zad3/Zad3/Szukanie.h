#pragma once
#include "Bloczki.h"
#include <vector>
using namespace std;

#include <iostream>
#include <vector>
#include <memory>

struct ElementDrzewa {
public:
    ElementDrzewa* rodzic;  
    ElementDrzewa** dzieci;
    int liczbaDzieci;
    Plansza * plansza;  
    Ruch * ruch; 

};
typedef ElementDrzewa* Drzewo;

void SzukajWGlab(Drzewo drzwo);
void SzukajWGlab(Drzewo drzwo, int liczbaRuchow, int & minimalna, Drzewo & wynik);
void dodajDziecko(Drzewo drzwo, Ruch ruch, int index);
