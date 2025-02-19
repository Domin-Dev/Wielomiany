#include "Bloczki.h"

#include <fstream>
#include <vector>
#include <iostream>

using namespace std;


	Plansza::Plansza(int szerokosc, int wysokosc)
	{
		this->szerokosc = szerokosc;
		this->wysokosc = wysokosc;
		bloczki = new Bloczek **[szerokosc];
		for (int i = 0; i < szerokosc; ++i)
		{
			bloczki[i] = new Bloczek *[wysokosc];
			for (size_t k = 0; k < wysokosc; k++)
			{
				bloczki[i][k] = NULL;
			}
		}
	}
	Plansza::Plansza(Plansza & plansza)
	{
		this->szerokosc = plansza.szerokosc;
		this->wysokosc = plansza.wysokosc;

		bloczki = new Bloczek **[szerokosc];
		for (int i = 0; i < szerokosc; ++i)
		{
			bloczki[i] = new Bloczek * [wysokosc];
			for (size_t k = 0; k < wysokosc; k++)
			{
				bloczki[i][k] = NULL;
			}
		}

		for (size_t i = 0; i < wysokosc; i++)
		{
			for (size_t j = 0; j < szerokosc; j++)
			{
				char c = plansza.pobierzChar(j, i);
				if (c == '#' || c == '-')
				{
					bloczki[j][i] = new Bloczek(j, i, c);
				}
				else
				{
					bloczki[j][i] = new DynamicznyBloczek(j,i, c);
				}
			}
		}
	}

	void Plansza::wczytajPlansze(ifstream* file)
	{
		string wiersz;
		int y = 0, x = 0;
		while ((*file) >> wiersz)
		{
			for (size_t i = 0; i < wiersz.length(); i++)
			{
				char c = wiersz.at(i);
				if (c == '#' || c == '-')
				{
					bloczki[x][y] = new Bloczek(x, y, c);
				}
				else
				{
					bloczki[x][y] = new DynamicznyBloczek(x, y, c);
				}
				x++;
			}
			x = 0;
			y++;
		}

		zaktualizujPlansze();
	}
	void Plansza::wyswietlPlansze()
	{
		for (size_t i = 0; i < wysokosc; i++)
		{
			for (size_t j = 0; j < szerokosc; j++)
			{
				cout << bloczki[j][i]->pobierzZnak();
			}
			cout << endl;
		}
	}

	bool Plansza::wolnePole(int x, int y)
	{
		if (x < szerokosc && x >= 0 && y >= 0 && y < wysokosc)
			return bloczki[x][y]->pobierzZnak() == '-';
		else
			return false;
	}
	bool Plansza::takiSamZnak(int x, int y, char c)
	{
		if (x < szerokosc && x >= 0 && y >= 0 && y < wysokosc)
		{
			if (bloczki[x][y] != 0)
				return bloczki[x][y]->pobierzZnak() == c;
		}
		return false;
	}
	vector<Ruch> Plansza::pobierzRuchy()
	{
		vector<Ruch> ruchy;
		for (int i = 0; i < wysokosc; i++)
		{
			for (int j = 0; j < szerokosc; j++)
			{
				Bloczek* bloczek = bloczki[j][i];
				if (typeid(*bloczek) == typeid(DynamicznyBloczek))
				{
					if (wolnePole(j + 1, i))
					{
						ruchy.push_back(Ruch(j, i, bloczek->pobierzZnak(), true));
					}
					if (wolnePole(j - 1, i))
					{
						ruchy.push_back(Ruch(j, i, bloczek->pobierzZnak(), false));
					}
				}
			}
		}
		return  ruchy;
	}

	void Plansza::zaktualizujPlansze()
	{
		do
		{
			grawitacja();
		} while (usunKlocki());
	}

	bool Plansza::usunKlocki()
	{
		bool zmiana = false;
		for (size_t i = 0; i < wysokosc; i++)
		{
			for (size_t j = 0; j < szerokosc; j++)
			{
				Bloczek* bloczek = bloczki[j][i];
				if (typeid(*bloczek) == typeid(DynamicznyBloczek))
				{
					if (usunKlockiDlaDanego(*bloczek, false))
						zmiana = true;
				}
			}
		}
		return zmiana;
	}
	bool Plansza::usunKlockiDlaDanego(Bloczek bloczek, bool usun)
	{
		int x, y;
		char c = bloczek.pobierzZnak();
		bloczek.pobierzPozycje(x, y);

		vector<Bloczek> list;
		if (takiSamZnak(x + 1, y, c))
		{
			list.push_back(*bloczki[x + 1][y]);
		}
		if (takiSamZnak(x - 1, y, c))
		{
			list.push_back(*bloczki[x - 1][y]);
		}
		if (takiSamZnak(x, y + 1, c))
		{
			list.push_back(*bloczki[x][y + 1]);
		}
		if (takiSamZnak(x, y - 1, c))
		{
			list.push_back(*bloczki[x][y - 1]);
		}

		if (usun || list.size() > 0)
		{
			delete bloczki[x][y];
			usun = true;
			bloczki[x][y] = new Bloczek(x, y, '-');
		}
		for (Bloczek b : list)
		{
			usunKlockiDlaDanego(b, true);
		}

		return usun;
	}

	void Plansza::grawitacja()
	{
		for (int i = wysokosc - 1; i >= 0; i--)
		{
			for (int j = 0; j < szerokosc; j++)
			{
				Bloczek* bloczek = bloczki[j][i];
				if (typeid(*bloczek) == typeid(DynamicznyBloczek))
				{
					grawitacjaDlaDanego(*bloczek);
				}
			}
		}
	}
	void Plansza::grawitacjaDlaDanego(Bloczek bloczek)
	{
		int x, y;
		bloczek.pobierzPozycje(x, y);
		int newY = y;
		while (wolnePole(x, newY + 1))
		{
			newY++;
		}

		if (newY != y)
		{
			DynamicznyBloczek* dBloczek = dynamic_cast<DynamicznyBloczek*>(bloczki[x][y]);
			dBloczek->zmienPozycje(x, newY);
			delete bloczki[x][newY];
			bloczki[x][newY] = bloczki[x][y];
			bloczki[x][y] = new Bloczek(x, y, '-');
		}
	}

	void Plansza::wykonajRuch(Ruch ruch)
	{
		int x = ruch.posX;
		int y = ruch.posY;

		DynamicznyBloczek* dBloczek = dynamic_cast<DynamicznyBloczek*>(bloczki[x][y]);
		int newX = x - 1;
		if (ruch.wPrawo) newX = x + 1;

		dBloczek->zmienPozycje(newX, y);
		delete bloczki[newX][y];
		bloczki[newX][y] = bloczki[x][y];
		bloczki[x][y] = new Bloczek(x, y, '-');
		zaktualizujPlansze();
	}
	char Plansza::pobierzChar(int x, int y)
	{
		if (x < szerokosc && x >= 0 && y >= 0 && y < wysokosc)
			return bloczki[x][y]->pobierzZnak();
		return 'e';
	}


	bool Plansza::wygrana()
	{
		for (int i = wysokosc - 1; i >= 0; i--)
		{
			for (int j = 0; j < szerokosc; j++)
			{
				Bloczek* bloczek = bloczki[j][i];
				if (typeid(*bloczek) == typeid(DynamicznyBloczek))
				{
					return false;
				}
			}
		}
		return true;
	}