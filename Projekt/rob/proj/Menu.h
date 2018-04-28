#pragma once
#include "Plansza.h"
#include "Gracz.h"
#include <iostream>
#include <fstream>
using namespace std;

//funkcja wybiera, któremu graczowi najpierw wylosowaæ klocki
void ktoPierwszyLosuje(gracz& nr1, gracz& nr2, int kol, zestaw& z);
bool gdzieWstawicKlocek(plansza& p, gracz& g, int wybor);
//wersja metody dla gracza komputerowego, bez menu wyboru, bez komunikatów
bool gdzieWstawicKlocekKomputer(plansza& p, gracz& g, int wybor);
int wielokrotnoscPiatki(int l_punktow);
//wyliczenie punktów i wyœwietlenie odpowiednich komunikatów, gdy gracz odda³ swój ostatni kamieñ
void zeroKart(gracz& zwyciezca, gracz& przegrany);
//Jeœli skoñczy³y siê karty w zestawie i ¿aden z graczy nie mo¿e wy³o¿yæ klocka,
//to wybierany jest zwyciêzca rundy i doliczane s¹ mu punkty
void zeroKartWTalii(gracz& nr1, gracz& nr2);
//funkcja wyœwietla menu g³ówne i zwraca nr opcji wybranej przez u¿ytkownika
int menuGlowne();	
//menu wewnêtrzne, wybór gry z komputerem, b¹dŸ z drugim graczem
int subMenu();
//menu do wyboru limitu punktów w grze, zwraca limit pkt, lub 0 - dodatkowo wybiera sie tu imiona graczy
int limitPunktow(string& imie1, string& imie2, int formaGry);
//Funkcja dodaje odpowiedni¹ iloœæ punktów do konta gracza
int dodawaniePunktow(gracz& g, plansza p);
//Wyœwietla informacje o grze
void info();
//funkcja sprawdza kto ma wiêcej pkt i wypisuje zwyciêzcê
void ktoWygral(gracz g1, gracz g2);
//funkcja zapisuje wynik gry do pliku
void zapiszWynik(gracz g1, gracz g2, string n_pliku);
//funkcja odczytuje wyniki gry
void odczytajWyniki(string n_pliku);
//funkcja zapisuje grê (jeœli wybór == 1, drugi gracz to komputer, w p.w. 2) 
void zapiszGre(zestaw z, plansza p, gracz nr1, gracz nr2, int kolejnosc, int limitPkt, int wybor);
//funkcja wczytuje grê
bool wczytajGre(zestaw& z, plansza& p, gracz& nr1, gracz& nr2, int& kolejnosc, int& limitPkt, int& wybor);

//kontrola poprawnoœci danych (SZABLON FUNKCJI)
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

