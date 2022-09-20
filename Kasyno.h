#pragma once
#include <iostream>
#include "Karta.h"
#include "Gracz.h"
#include "Bot.h"
#include "fstream"

class Kasyno
{
	Gracz* uczestnicy[6];
	int iloscWydanychKart;
	int iloscUczestnikow;
	Karta talia[52];
	void graczeWchodzaDoKasyna();
	void graczeWychodzaZKasyna();
public:
	Kasyno();
	Kasyno(const Kasyno& inneKasyno);
	~Kasyno();
	Karta* dajKarte();
	void tasowanie();
	void graj();
	Kasyno& operator=(const  Kasyno& inneKasyno);
};