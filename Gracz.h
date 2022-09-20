#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "Karta.h"

using namespace std;

class Kasyno;
class Gracz
{
	friend ostream& operator<<(ostream& s, const Gracz& _gracz);
protected:
	Kasyno* lokalizacja;
	Karta* reka[10];
	int iloscKart;
	int sumaPunktow;
	bool pas;
	char nazwa[20];
	void setNazwa();
public:
	Gracz();
	Gracz(Kasyno* _lokalizacja);
	Gracz(Gracz& innyGracz, Kasyno* _lokalizacja);
	void wezKarte(Karta* _karta);
	void wyswietl() const;
	void wyswietl(ofstream& plik) const;
	bool getPas() const { return pas; };
	int getSumaPunktow() const { return sumaPunktow; };
	virtual void graj();
	void przygotujSieDoNowejGry();
	virtual int getOdwaga() { return 0; }
};

ostream& operator<<(ostream& s, const Gracz& _gracz);

