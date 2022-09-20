#include "Gracz.h"
#include "Kasyno.h"

Gracz::Gracz()
	: iloscKart(0), sumaPunktow(0), pas(0), lokalizacja(nullptr)
{
	for (int i = 0; i < 10; i++)
	{
		reka[i] = nullptr;
	}
	nazwa[0] = 0;
}

Gracz::Gracz(Kasyno* _lokalizacja)
	: iloscKart(0), sumaPunktow(0), pas(0), lokalizacja(_lokalizacja)
{
	for (int i = 0; i < 10; i++)
	{
		reka[i] = nullptr;
	}
	setNazwa();
}

Gracz::Gracz(Gracz& innyGracz, Kasyno* _lokalizacja)
	: iloscKart(0), sumaPunktow(0), pas(0), lokalizacja(_lokalizacja)
{
	for (int i = 0; i < 10; i++)
	{
		reka[i] = nullptr;
	}
	strcpy(nazwa, innyGracz.nazwa);
}

void Gracz::wezKarte(Karta* _karta)
{
	reka[iloscKart] = _karta;
	sumaPunktow += (_karta->getWartosc());
	iloscKart++;
	if (sumaPunktow >= 21) pas = 1;
}

void Gracz::wyswietl() const
{
	cout << nazwa << " ma takie karty:" << endl;
	for (int i = 0; i < iloscKart; i++)
	{
		cout << i + 1 << ". ";cout << *(reka[i]);
		cout << endl;
	}
	cout << "Suma punktow: " << sumaPunktow << endl;
}

void Gracz::wyswietl(ofstream& plik) const
{
	plik << nazwa << " ma takie karty:" << endl;
	for (int i = 0; i < iloscKart; i++)
	{
		plik << i + 1 << ". "; plik << *(reka[i]);
		plik << endl;
	}
	plik << "Suma punktow: " << sumaPunktow << endl;
}

void Gracz::graj()
{
	if (lokalizacja != nullptr)
	{
		if (pas == 0)
		{
			int decyzja;
			system("cls");
			cout << nazwa << " teraz bedzie grac." << endl;
			system("pause");
			system("cls");
			wyswietl();
			cout << "1. Dobierz karte" << endl << "2. Spasuj" << endl;
			cin >> decyzja;
			while ((cin.fail() == 1) || (decyzja < 1) || (decyzja > 2))
			{
				cin.clear();
				cin.ignore(256, '\n');
				cin >> decyzja;
			}
			if (decyzja == 2) pas = 1;
			else
			{
				wezKarte(lokalizacja->dajKarte());
				cout << "Dobrano " << *reka[iloscKart - 1] << endl << "Nowa suma punktow to " << sumaPunktow << endl;
				system("pause");
			}
		}
		else
		{
			system("cls");
			cout << nazwa << " spasowal." << endl;
			system("pause");
		}
	}
}

void Gracz::setNazwa()
{
	int znak, i;
	bool czyJestCos = 0;
	i = 0;
	cout << "Podaj swoja nazwe: ";
	while (true)
	{
		znak = getchar();
		while (znak == 10 && czyJestCos == 0) znak = getchar();
		if (znak == 32) i--;
		else if ((znak != EOF) && (znak != '\n'))
		{
			nazwa[i] = znak;
			czyJestCos = 1;
		}
		else
		{
			nazwa[i] = 0;
			break;
		}
		i++;
		if (i >= 19)
		{
			printf("\nProsze podac krotsza fraze! Maksymalna dozwolona dlugosc to 19 znakow.\n\n");
			while (((znak = getchar()) != '\n') && (znak != EOF));
			i = 0;
		}
	}
	
}

void Gracz::przygotujSieDoNowejGry()
{
	iloscKart = 0;
	for (int i = 0; i < 10; i++)
	{
		reka[i] = nullptr;
	}
	pas = 0;
	sumaPunktow = 0;
}

ostream& operator<<(ostream& s, const Gracz& _gracz)
{
	return s << _gracz.nazwa;
}