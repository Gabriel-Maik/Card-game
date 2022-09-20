#include "Kasyno.h"
#include <time.h>

Kasyno::Kasyno()
	: iloscWydanychKart(0)
{
	int k;
	srand(time(NULL));
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 13; j++)
		{
			k = 13 * i + j;
			talia[k].setKolor(i);
			talia[k].setWartosc(j);
		}
	}
	tasowanie();
	graczeWchodzaDoKasyna();
}

Kasyno::Kasyno(const Kasyno& inneKasyno)
	: iloscWydanychKart(inneKasyno.iloscWydanychKart),
	iloscUczestnikow(inneKasyno.iloscUczestnikow)
{
	for (int i = 0; i < 52; i++)
	{
		talia[i] = inneKasyno.talia[i];
	}
	int numerBota = 1;
	for (int i = 0; i < iloscUczestnikow; i++)
	{
		if (inneKasyno.uczestnicy[i]->getOdwaga())
		{
			uczestnicy[i] = new Bot(this, numerBota, inneKasyno.uczestnicy[i]->getOdwaga());
			numerBota++;
		}
		else uczestnicy[i] = new Gracz(*(inneKasyno.uczestnicy[i]), this);
	}
}

Kasyno::~Kasyno()
{
	graczeWychodzaZKasyna();
}

void Kasyno::graczeWchodzaDoKasyna()
{
	int decyzja;
	cout << "Ilosc graczy ludzkich (1-3): ";
	cin >> decyzja;
	while ((cin.fail() == 1) || (decyzja < 1) || (decyzja > 3))
	{
		cin.clear();
		cin.ignore(256, '\n');
		cin >> decyzja;
	}
	iloscUczestnikow = 0;
	for (int i = 0; i < decyzja; i++)
	{
		uczestnicy[iloscUczestnikow] = new Gracz(this);
		iloscUczestnikow++;
	}
	cout << "Ilosc graczy komputerowych (1-3): ";
	cin >> decyzja;
	while ((cin.fail() == 1) || (decyzja < 1) || (decyzja > 3))
	{
		cin.clear();
		cin.ignore(256, '\n');
		cin >> decyzja;
	}
	for (int i = 0; i < decyzja; i++)
	{
		uczestnicy[iloscUczestnikow] = new Bot(this, i + 1, 15 + (rand() % 5));
		iloscUczestnikow++;
	}
}

void Kasyno::graczeWychodzaZKasyna()
{
	while (iloscUczestnikow > 0)
	{
		iloscUczestnikow--;
		delete uczestnicy[iloscUczestnikow];
	}
}

void Kasyno::tasowanie()// tasowane sa tylko karty niewydane
{
	Karta tymczasowa;
	int los1, los2;
	for (int i = 0; i < 100; i++)
	{
		los1 = rand() % 52;
		los2 = rand() % 52;
		if ((los1 >= iloscWydanychKart) && (los2 >= iloscWydanychKart) && (los1 != los2))
		{
			tymczasowa = talia[los1];
			talia[los1] = talia[los2];
			talia[los2] = tymczasowa;
		}
		else i--;
	}
}

Karta* Kasyno::dajKarte()
{
	iloscWydanychKart++;
	return &(talia[iloscWydanychKart - 1]);
}

void Kasyno::graj()
{
	bool czyKtosGra = true;
	bool czyGrac = true;
	bool czyZmienicGraczy = false;
	if(iloscUczestnikow)
	{
		int iloscBotow = 0;
		for (int i = 0; i < iloscUczestnikow; i++) if (uczestnicy[i]->getOdwaga()) iloscBotow++;
		if (!((iloscBotow != iloscUczestnikow) && (iloscBotow > 0) && (iloscUczestnikow > 1)))
		{
			graczeWychodzaZKasyna();
			graczeWchodzaDoKasyna();
		}
	}
	else graczeWchodzaDoKasyna();
	while (czyGrac)
	{
		for (int i = 0; i < 2; i++)
		{
			for (int j = 0; j < iloscUczestnikow; j++) uczestnicy[j]->wezKarte(dajKarte());
		}
		czyKtosGra = true;
		do
		{
			czyKtosGra = false;
			for (int j = 0; j < iloscUczestnikow; j++)
			{
				uczestnicy[j]->graj();
				if (uczestnicy[j]->getPas() == 0) czyKtosGra = true;
			}
		} while (czyKtosGra);
		system("cls");
		cout << "Partia zakonczona" << endl;
		for (int j = 0; j < iloscUczestnikow; j++) uczestnicy[j]->wyswietl();
		ofstream plik;
		plik.open("Ostatnia partia.txt", ifstream::out);
		for (int j = 0; j < iloscUczestnikow; j++) uczestnicy[j]->wyswietl(plik);
		int najlepszyWynik = 0;
		for (int j = 0; j < iloscUczestnikow; j++) if ((uczestnicy[j]->getSumaPunktow() > najlepszyWynik) && (uczestnicy[j]->getSumaPunktow() < 22)) najlepszyWynik = uczestnicy[j]->getSumaPunktow();
		if (najlepszyWynik > 0)
		{
			cout << "Wygrywa ";
			plik << "Wygrywa ";
			bool czyNastepny = false;
			for (int j = 0; j < iloscUczestnikow; j++) if (uczestnicy[j]->getSumaPunktow() == najlepszyWynik)
			{
				if (czyNastepny)
				{
					cout << " i ";
					plik << " i ";
				}
				else czyNastepny = true;
				cout << *uczestnicy[j];
				plik << *uczestnicy[j];
			}
			cout << "." << endl;
			plik << "." << endl;
		}
		else
		{
			cout << "Wszyscy przegrywaja..." << endl;
			plik << "Wszyscy przegrywaja..." << endl;
		}
		system("pause");
		system("cls");
		cout << "Czy rozegrac kolejna partie?\n1. Tak\n2. Nie\n";
		int decyzja;
		cin >> decyzja;
		while ((cin.fail() == 1) || (decyzja < 1) || (decyzja > 2))
		{
			cin.clear();
			cin.ignore(256, '\n');
			cin >> decyzja;
		}
		if (decyzja == 2)
		{
			czyGrac = false;
		}
		else
		{
			system("cls");
			cout << "Czy zmienic graczy?\n1. Tak\n2. Nie\n";
			cin >> decyzja;
			while ((cin.fail() == 1) || (decyzja < 1) || (decyzja > 2))
			{
				cin.clear();
				cin.ignore(256, '\n');
				cin >> decyzja;
			}
			if (decyzja == 1)
			{
				graczeWychodzaZKasyna();
				graczeWchodzaDoKasyna();
			}
			iloscWydanychKart = 0;
			tasowanie();
		}
		for (int j = 0; j < iloscUczestnikow; j++) uczestnicy[j]->przygotujSieDoNowejGry();
	}
}

Kasyno& Kasyno::operator=(const Kasyno& inneKasyno)
{
	if (&inneKasyno == this) return *this;
	else
	{
		graczeWychodzaZKasyna();
		iloscWydanychKart = inneKasyno.iloscWydanychKart;
		iloscUczestnikow = inneKasyno.iloscUczestnikow;
		for (int i = 0; i < 52; i++)
		{
			talia[i] = inneKasyno.talia[i];
		}
		int numerBota = 1;
		for (int i = 0; i < iloscUczestnikow; i++)
		{
			if (inneKasyno.uczestnicy[i]->getOdwaga())
			{
				uczestnicy[i] = new Bot(this, numerBota, inneKasyno.uczestnicy[i]->getOdwaga());
				numerBota++;
			}
			else uczestnicy[i] = new Gracz(*(inneKasyno.uczestnicy[i]), this);
		}
		return *this;
	}
}