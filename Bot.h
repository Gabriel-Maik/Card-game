#pragma once
#include "Gracz.h"

class Kasyno;
class Bot :
	public Gracz
{
	int odwaga;
public:
	Bot(Kasyno* _lokalizacja, int numer, int _odwaga = 17);
	virtual void graj();
	virtual int getOdwaga() { return odwaga; }
};

