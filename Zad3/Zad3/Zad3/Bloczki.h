#pragma once
#include <fstream>
#include <vector>


class Bloczek
{
protected:
	char znak;
	int posX;
	int posY;

public:
	Bloczek(int posX, int posY, char znak);
	Bloczek();
	virtual char pobierzZnak();
	void pobierzPozycje(int& x, int& y);
	bool porownaj(Bloczek b);
};

class DynamicznyBloczek : public Bloczek
{
public:
	DynamicznyBloczek(int posX, int posY, char znak) : Bloczek(posX, posY, znak) {}

	void zmienPozycje(int posX, int posY) { this->posX = posX;this->posY = posY; }
};

class Ruch
{

public:
	int posX;
	int posY;
	char znak;
	bool wPrawo; // true - prawo / false - lewo

	Ruch(int posX, int posY, char znak, bool wPrawo);

	void wyswietl();
};	

class Plansza
{
	Bloczek*** bloczki;
	int szerokosc;
	int wysokosc;

	bool usunKlocki();
	bool usunKlockiDlaDanego(Bloczek bloczek, bool usun);
	void grawitacja();
	void grawitacjaDlaDanego(Bloczek bloczek);
	bool wolnePole(int x, int y);
	bool takiSamZnak(int x, int y, char c);
	char pobierzChar(int x, int y);
	bool jestZnak(Bloczek blok);

public:
	Plansza(int szerokosc, int wysokosc);
	Plansza(Plansza &plansza);
	void wczytajPlansze(std::ifstream* file);
	void wyswietlPlansze();
	std::vector<Ruch> pobierzRuchy();
	void zaktualizujPlansze();
	void wykonajRuch(Ruch ruch);
	bool wygrana();
	bool moznaUkonczyc();
};