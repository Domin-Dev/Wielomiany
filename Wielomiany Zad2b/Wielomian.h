#pragma once
#include <iostream>
#include <string>

using namespace std;

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
//	
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



class BazaWielomianu
{
	protected:
		int stopien;
	public:
		int pobierzStopien() const { return stopien; }
		virtual double operator[](int index) const = 0;
		string Pokaz() const;
};

class Jednomian : public BazaWielomianu
{
	protected:
		double wartosc;
	public:
		double operator[](int index) const override;
		double operator()(int index);
		Jednomian(double wartosc, int stopien);
		Jednomian Pochodna();
};

class Wielomian : public BazaWielomianu
{
	double* wsp;

	char* AnalizujJednomian(const char* napis);
	void Analizuj(const char* napis);
	void Powieksz(int stopien);
	void WeryfikujStopien();
	Wielomian& Dzielenie(const Wielomian& w1, Wielomian& reszta);
protected:	
		void InicjujWielomian(int stopien);
public:
		double operator[](int index) const override;
		double operator()(int index);
		Wielomian(const char* napis);
		Wielomian(const Wielomian& w);
		Wielomian(const BazaWielomianu& b);
		Wielomian(int stopien);
		Wielomian();
		Wielomian(int stopien, double* wsp);

		Wielomian Pochodna();
		Wielomian& operator+=(const BazaWielomianu& w1);
		Wielomian& operator-=(const BazaWielomianu& w1);
		Wielomian& operator*=(const BazaWielomianu& w1);
		Wielomian& operator/=(const BazaWielomianu& w1);

		Wielomian& operator+=(const double& d);
		Wielomian& operator-=(const double& d);
		Wielomian& operator*=(const double& d);
		Wielomian& operator/=(const double& d);

		Wielomian& operator=(const BazaWielomianu& w1);



		~Wielomian() { delete[]wsp; }

};

Wielomian operator+(const BazaWielomianu& w1, const BazaWielomianu& w2);
Wielomian operator+(const BazaWielomianu& w1, const double& d);
Wielomian operator+(const double& d, const BazaWielomianu& w1);

Wielomian operator-(const BazaWielomianu& w1, const BazaWielomianu& w2);
Wielomian operator-(const BazaWielomianu& w1, const double& d);
Wielomian operator-(const double& d, const BazaWielomianu& w1);

Wielomian operator*(const BazaWielomianu& w1, const BazaWielomianu& w2);
Wielomian operator*(const BazaWielomianu& w1, const double& d);
Wielomian operator*(const double& d, const BazaWielomianu& w1);