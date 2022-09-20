#include "Bot.h"
#include "Kasyno.h"


Bot::Bot(Kasyno* _lokalizacja, int numer, int _odwaga)
{
	char numerBota[2];
	lokalizacja = _lokalizacja;
	strcpy(nazwa, "Bot");
	if ((numer > 0) && (numer < 4))
	{
		numerBota[0] = 48 + numer;
		numerBota[1] = 0;
		strcat(nazwa, numerBota);
	}
	odwaga = _odwaga;
}

void Bot::graj()
{
	if (lokalizacja != nullptr)
	{
		if (pas == 0)
		{
			int decyzja;
			system("cls");
			if (sumaPunktow <= odwaga)
			{
				cout << nazwa << " dobiera karte." << endl;
				wezKarte(lokalizacja->dajKarte());
			}
			else
			{
				pas = 1;
				cout << nazwa << " pasuje." << endl;
			}
		}
		else
		{
			system("cls");
			cout << nazwa << " spasowal." << endl;
		}
		system("pause");
	}
}
