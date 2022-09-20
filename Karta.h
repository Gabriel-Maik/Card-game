#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>

class Karta {
private:
	char kolor;
	char figura;
	int wartosc;
public:
	Karta(int _kolor = 0, int _wartosc = 0);
	void setKolor(int _kolor);
	void setWartosc(int _wartosc);
	char getKolor() const { return kolor; }
	char getFigura() const { return figura; }
	int getWartosc() const { return wartosc; }
	void wypisz() const { std::cout << figura << kolor; }
};

std::ostream& operator <<(std::ostream& s, const Karta& _karta);