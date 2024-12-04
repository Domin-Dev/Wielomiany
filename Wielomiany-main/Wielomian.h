#pragma once
#include <iostream>
//
//class Wielomian
//{
//	char* AnalizujJednomian(const char* napis);
//	void Analizuj(const char* napis);
//	void Powieksz(int stopien);
//	void WeryfikujStopien();
//	Wielomian& Dzielenie(const Wielomian& w1, Wielomian& reszta);
//
//
//	protected:
//		double* wsp;
//		int stopien;
//		void InicjujWielomian(int stopien);
//	public:
//		Wielomian(const char* napis);
//		Wielomian(const Wielomian& w);
//		Wielomian(int stopien);
//		Wielomian();
//		Wielomian(int stopien, double* wsp);
//
//		void Pokaz();
//		Wielomian Pochodna();
//		Wielomian& operator+=(const Wielomian& w1);
//		Wielomian& operator+=(const double& d);
//
//		Wielomian& operator-=(const Wielomian& w1);
//		Wielomian& operator-=(const double& d);
//
//		Wielomian& operator*=(const Wielomian& w1);
//		Wielomian& operator*=(const double& d);
//
//		Wielomian& operator/=(const Wielomian& w1);
//		Wielomian& operator/=(const double& d);
//
//		Wielomian& operator%=(const Wielomian& w1);
//		Wielomian& operator=(const Wielomian& w1);
//		
//		friend std::ostream& operator<<(std::ostream& os, const Wielomian& w);
//		friend std::istream& operator>>(std::istream& is, Wielomian& w);
//
//		friend Wielomian operator/(const Wielomian& w1, const double& d);
//
//		friend Wielomian operator-(const double& d, const Wielomian& w1);
//		
//		double operator[](int index);
//		double operator()(int index);
//		~Wielomian() { delete[]wsp; }
//}; 
//

//
//Wielomian operator+(const Wielomian& w1, const Wielomian& w2);
//Wielomian operator+(const Wielomian& w1, const double& d);
//Wielomian operator+(const double& d    , const Wielomian& w1);
//
//Wielomian operator-(const Wielomian& w1, const Wielomian& w2);
//Wielomian operator-(const Wielomian& w1, const double& d);
//
//
//Wielomian operator/(const Wielomian& w1, const Wielomian& w2);
//Wielomian operator/(const double& d, const Wielomian& w1);
//
//
//Wielomian operator*(const Wielomian& w1, const Wielomian& w2);
//Wielomian operator*(const Wielomian& w1, const double& d);
//Wielomian operator*(const double& d, const Wielomian& w1);
//
//Wielomian operator%(const Wielomian& w1, const Wielomian& w2);
//Wielomian operator%(const Wielomian& w1, const double& d);
//Wielomian operator%(const double& d, const Wielomian& w1);
//
//class Jednomian : public Wielomian
//{
//	public:
//		Jednomian(int stopien, double wartosc);
//};


class BazaWielomianu
{
	protected:
		int stopien;

	public:
		virtual double operator[](int index) {};
		virtual void Pokaz(){};
};

class Jednomian : public BazaWielomianu
{
	double wartosc;

	public:
		double operator[](int index);

};


class Wielomian : public BazaWielomianu
{
	double* wsp;

	char* AnalizujJednomian(const char* napis);
	void Analizuj(const char* napis);
	void Powieksz(int stopien);
	void Weryfikujstopien();
	Wielomian& dzielenie(const Wielomian& w1, Wielomian& reszta);
protected:	
		void InicjujWielomian(int stopien);

public:
		double operator[](int index);
		Wielomian(const char* napis);
		Wielomian(const Wielomian& w);
		Wielomian(int stopien);
		Wielomian();
		Wielomian(int stopien, double* wsp);
		void Pokaz() override;
};
