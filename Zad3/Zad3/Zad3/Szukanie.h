#pragma once
#include "Bloczki.h"
#include <vector>
using namespace std;

#include <iostream>
#include <vector>
#include <memory>

class ElementDrzewa {
public:
    ElementDrzewa* rodzic;  // WskaŸnik do rodzica (jeœli istnieje)
    std::vector<std::unique_ptr<ElementDrzewa>> dzieci;  // Dzieci zarz¹dzane za pomoc¹ smart pointerów
    std::unique_ptr<Plansza> plansza;  // Przechowywanie planszy
    std::unique_ptr<Ruch> ruch;  // Przechowywanie ruchu


    ElementDrzewa(const ElementDrzewa& inny)
        : rodzic(nullptr),  // Rodzica nie kopiujemy, bêdzie ustawiany w kontekœcie wy¿szym
        plansza(inny.plansza ? std::make_unique<Plansza>(*inny.plansza) : nullptr),
        ruch(inny.ruch ? std::make_unique<Ruch>(*inny.ruch) : nullptr) {
        for (const auto& dziecko : inny.dzieci) {
            // Tworzymy kopiê ka¿dego dziecka i ustawiamy rodzica na "this"
            auto noweDziecko = std::make_unique<ElementDrzewa>(*dziecko);
            noweDziecko->rodzic = this;  // Ustawiamy rodzica dla skopiowanego dziecka
            dzieci.push_back(std::move(noweDziecko));
        }
    }

    // Operator przypisania (opcjonalnie, ale zalecany przy kopiowaniu)
    ElementDrzewa& operator=(const ElementDrzewa& inny) {
        if (this == &inny) return *this;  // Zabezpieczenie przed samoprzydzia³em

        // Czyszczenie istniej¹cych danych
        dzieci.clear();
        plansza.reset();
        ruch.reset();

        // Kopiowanie planszy i ruchu
        plansza = inny.plansza ? std::make_unique<Plansza>(*inny.plansza) : nullptr;
        ruch = inny.ruch ? std::make_unique<Ruch>(*inny.ruch) : nullptr;

        // Kopiowanie dzieci
        for (const auto& dziecko : inny.dzieci) {
            auto noweDziecko = std::make_unique<ElementDrzewa>(*dziecko);
            noweDziecko->rodzic = this;  // Ustawiamy rodzica na "this"
            dzieci.push_back(std::move(noweDziecko));
        }

        return *this;
    }
    // Konstruktor
    explicit ElementDrzewa(ElementDrzewa* rodzic = nullptr)
        : rodzic(rodzic), plansza(nullptr), ruch(nullptr) {}

    // Destruktor automatycznie usunie dzieci i zarz¹dzane obiekty
    ~ElementDrzewa() = default;

    // Dodawanie nowego dziecka
    ElementDrzewa* dodajDziecko() {
        // Tworzymy nowe dziecko i dodajemy je do wektora
        auto noweDziecko = std::make_unique<ElementDrzewa>(this);
        ElementDrzewa* dzieckoPtr = noweDziecko.get();  // Pobieramy wskaŸnik do dodawanego dziecka
        dzieci.push_back(std::move(noweDziecko));  // Przenosimy w³asnoœæ do wektora
        return dzieckoPtr;  // Zwracamy wskaŸnik do dodanego dziecka
    }

    // Pobieranie liczby dzieci
    size_t liczbaDzieci() const {
        return dzieci.size();
    }

    // Sprawdzenie, czy wêze³ jest liœciem
    bool isLeaf() const {
        return dzieci.empty();
    }

    // Ustawienie planszy (przyk³ad zarz¹dzania obiektami)
    void ustawPlansze(std::unique_ptr<Plansza> nowaPlansza) {
        plansza = std::move(nowaPlansza);
    }

    // Ustawienie ruchu
    void ustawRuch(std::unique_ptr<Ruch> nowyRuch) {
        ruch = std::move(nowyRuch);
    }

    // Funkcja wyœwietlaj¹ca informacje o wêŸle i jego dzieciach (rekurencyjna)
    void wyswietlInformacje(int poziom = 0) const {
        for (int i = 0; i < poziom; ++i) std::cout << "-";
        std::cout << "Wezel na poziomie " << poziom
            << ", liczba dzieci: " << dzieci.size() << std::endl;

        for (const auto& dziecko : dzieci) {
            dziecko->wyswietlInformacje(poziom + 1);
        }
    }
};
typedef ElementDrzewa* Drzewo;

void SzukajWGlab(Drzewo drzwo);
void SzukajWGlab(Drzewo drzwo, int liczbaRuchow, int minimalna, Drzewo* wynik);
Drzewo dodajDziecko(Drzewo drzwo, Ruch ruch);
