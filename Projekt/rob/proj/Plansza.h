#pragma once
#include "Klocki.h"
#include <cstdlib>

class plansza{
	klocek lista[28];			//na planszy mo�e by� maksymalnie 28 klock�w (bo tyle jest w zestawie)
	int l_klockow;				//liczba klock�w aktualnie na planszy
public:
	plansza() :l_klockow(0){};
	void wypiszKlocki();		//wypisanie listy klockow
	klocek dodajOdLewej(klocek k);	//dodanie klocka od lewej strony
	klocek dodajOdPrawej(klocek k);	//i od prawej
	klocek sprawdzOdLewejIWstaw(klocek k);	//sprawdzenie, czy mo�na wstawi� klocek od lewej i ewentualne wstawienie
	klocek sprawdzOdPrawejIWstaw(klocek k);	//sprawdzenie, czy mo�na wstawi� klocek od prawej i ewentualne wstawienie
	bool sprawdzOdPrawej(klocek k);	//samo sprawdzenie
	bool sprawdzOdLewej(klocek k);	//samo sprawdzenie
	klocek podajLewy();		//podanie klocka po lewej stronie planszy
	klocek podajPrawy();	//podanie klocka po prawej stronie planszy
	klocek podajKlocek(int nr);	//podanie klocka o danym numerze
	klocek usunKlocek(int nr);	//usuni�cie klocka o danym numerze z planszy
	int podajLiczbe(){ return l_klockow; };
	void wyczyscPlansze(zestaw &z);	//czy�ci plansz� i wrzuca wszystko do zestawu
};