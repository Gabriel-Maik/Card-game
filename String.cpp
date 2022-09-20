#include "String.h"

char* String::zawartosc()
{
	return tab;
}
String& String::operator=(const String &_zrodlo)
{
	if (&_zrodlo == this) return *this;
	rozmiar = _zrodlo.rozmiar;
	delete[] tab;
	tab = new char[rozmiar];
	strcpy(tab, _zrodlo.tab);
	return *this;
}
String::String(const String &_zrodlo)
{
	rozmiar = _zrodlo.rozmiar;
	tab = new char[rozmiar];
	strcpy(tab, _zrodlo.tab);
}
String::String()
	: rozmiar(0)
	, tab(nullptr)
{}
String::String(const char *_src)
{
	rozmiar = strlen(_src) + 1;
	tab = new char[rozmiar];
	strcpy(tab, _src);
}
String::~String()
{
	delete[] tab;
}