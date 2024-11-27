#pragma once
class Wielomian
{
	double* wsp;
	int stopien;
	void InicjujWielomian(int stopien);
	char* AnalizujJednomian(const char* napis);
	void Analizuj(const char* napis);
	void Powieksz(int stopien);
	void WeryfikujStopien();
	Wielomian& Dzielenie(const Wielomian& w1, Wielomian& reszta);

	public:
		Wielomian(const char* napis);
		Wielomian(const Wielomian& w);
		Wielomian(int stopien);
		Wielomian();
		Wielomian(int stopien, double* wsp);

		void Pokaz();
		Wielomian Pochodna();
		Wielomian& operator+=(const Wielomian& w1);
		Wielomian& operator-=(const Wielomian& w1);
		Wielomian& operator*=(const Wielomian& w1);
		Wielomian& operator*=(const double& d);
		Wielomian& operator/=(const Wielomian& w1);
		Wielomian& operator%=(const Wielomian& w1);
		Wielomian& operator=(const Wielomian& w1);
		double operator[](int index);
		~Wielomian() { delete[]wsp; }
}; 



Wielomian operator+(const Wielomian& w1, const Wielomian& w2);
Wielomian operator-(const Wielomian& w1, const Wielomian& w2);
Wielomian operator/(const Wielomian& w1, const Wielomian& w2);
Wielomian operator*(const Wielomian& w1, const Wielomian& w2);
Wielomian operator*(const Wielomian& w1, const double& d);
Wielomian operator%(const Wielomian& w1, const Wielomian& w2);