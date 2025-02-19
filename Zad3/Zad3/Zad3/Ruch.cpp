#include "Bloczki.h"
#include <iostream>

Ruch::Ruch(int posX, int posY, char znak, bool wPrawo)
{
	this->posX = posX;
	this->posY = posY;
	this->znak = znak;
	this->wPrawo = wPrawo;
}

void Ruch::wyswietl()
{
	char c = 'L';
	if (wPrawo) c = 'R';
	std::cout << "(" << znak << "," << posY << "," << posX << "," << c << ")" << std::endl;
}
