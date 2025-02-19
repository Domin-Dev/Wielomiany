#include "Bloczki.h"


	Bloczek::Bloczek(int posX, int posY, char znak)
	{
		this->posX = posX;
		this->posY = posY;
		this->znak = znak;
	}

	Bloczek::Bloczek()
	{
		posX = 0;
		posY = 0;
		znak = 0;
	}

	char Bloczek::pobierzZnak()
	{
		return znak;
	}

	void Bloczek::pobierzPozycje(int& x, int& y)
	{
		x = posX;
		y = posY;
	}
