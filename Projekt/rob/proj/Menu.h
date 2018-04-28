#pragma once
#include "Plansza.h"
#include "Gracz.h"
#include <iostream>
#include <fstream>
using namespace std;

//funkcja wybiera, kt�remu graczowi najpierw wylosowa� klocki
void ktoPierwszyLosuje(gracz& nr1, gracz& nr2, int kol, zestaw& z);
bool gdzieWstawicKlocek(plansza& p, gracz& g, int wybor);
//wersja metody dla gracza komputerowego, bez menu wyboru, bez komunikat�w
bool gdzieWstawicKlocekKomputer(plansza& p, gracz& g, int wybor);
int wielokrotnoscPiatki(int l_punktow);
//wyliczenie punkt�w i wy�wietlenie odpowiednich komunikat�w, gdy gracz odda� sw�j ostatni kamie�
void zeroKart(gracz& zwyciezca, gracz& przegrany);
//Je�li sko�czy�y si� karty w zestawie i �aden z graczy nie mo�e wy�o�y� klocka,
//to wybierany jest zwyci�zca rundy i doliczane s� mu punkty
void zeroKartWTalii(gracz& nr1, gracz& nr2);
//funkcja wy�wietla menu g��wne i zwraca nr opcji wybranej przez u�ytkownika
int menuGlowne();	
//menu wewn�trzne, wyb�r gry z komputerem, b�d� z drugim graczem
int subMenu();
//menu do wyboru limitu punkt�w w grze, zwraca limit pkt, lub 0 - dodatkowo wybiera sie tu imiona graczy
int limitPunktow(string& imie1, string& imie2, int formaGry);
//Funkcja dodaje odpowiedni� ilo�� punkt�w do konta gracza
int dodawaniePunktow(gracz& g, plansza p);
//Wy�wietla informacje o grze
void info();
//funkcja sprawdza kto ma wi�cej pkt i wypisuje zwyci�zc�
void ktoWygral(gracz g1, gracz g2);
//funkcja zapisuje wynik gry do pliku
void zapiszWynik(gracz g1, gracz g2, string n_pliku);
//funkcja odczytuje wyniki gry
void odczytajWyniki(string n_pliku);
//funkcja zapisuje gr� (je�li wyb�r == 1, drugi gracz to komputer, w p.w. 2) 
void zapiszGre(zestaw z, plansza p, gracz nr1, gracz nr2, int kolejnosc, int limitPkt, int wybor);
//funkcja wczytuje gr�
bool wczytajGre(zestaw& z, plansza& p, gracz& nr1, gracz& nr2, int& kolejnosc, int& limitPkt, int& wybor);

//kontrola poprawno�ci danych (SZABLON FUNKCJI)
template<typename T = int>
T kontrolaPopr(int d_granica, int g_granica){
	T dane;
	while (!(cin >> dane) || dane < d_granica || dane>g_granica){
		cout << "Bledne dane. Podaj jeszcze raz: ";
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
	}
	return dane;
}

template<typename T>
T kontrolaPopr(){
	T dane;
	while (!(cin >> dane)){
		cout << "Bledne dane. Podaj jeszcze raz: ";
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
	}
	return dane;
}

