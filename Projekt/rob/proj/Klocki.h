#pragma once
#include <iostream>
using namespace std;

class klocek{
	int pierwsza_l;		//pierwsza liczba oczek
	int druga_l;		//druga liczba oczek
public:
	klocek() :pierwsza_l(0), druga_l(0){};
	klocek(int a, int b) :pierwsza_l(a), druga_l(b){};
	//zmienia pierwsz� liczb� oczek
	void zmienPierwsza(int a){ pierwsza_l = a; };
	//zmienia drug� liczb� oczek
	void zmienDruga(int b){ druga_l = b; };
	//podaje pierwsz� liczb� oczek
	int podajPierwsza(){ return pierwsza_l; };
	//podaje drug� liczb� oczek
	int podajDruga(){ return druga_l; };
	//odwraca kolejno�� cyfr w domino, domy�lnie pierwsza cyfra nie mo�e by� wi�ksza od drugiej
	void odwrocKolejnosc();		
	//przeci��ony operator por�wnania, sprawdza, czy drugi klocek jest taki sam
	bool operator==(const klocek& k);
	//metoda sprawdza, czy klocek jest dublem
	bool czyJestDublem() { return pierwsza_l == druga_l; };
	//przeci��ony operator przypisania, kopiuje warto�ci z klocka po prawej do lewego
	klocek& operator=(const klocek& k){
		pierwsza_l = k.pierwsza_l;
		druga_l = k.druga_l;
		return *this;
	}
};

class zestaw{
	klocek klocki[28];	//zestaw klock�w
	int l_klockow;
public:
	zestaw();
	//wype�nia zestaw na nowo klockami
	void wypelnijKlockami();
	//wypisuje ca�y zestaw klock�w
	void wypiszZestaw();
	//wypisuje pojedynczy klocek
	void wypiszKlocek(int nr);
	//zwraca pojedynczy klocek
	klocek podajKlocek(int nr);
	//usuwa klocek o danym numerze
	klocek usunKlocek(int nr);
	//usuwa klocek podany jako argument
	klocek usunKlocek(klocek k);
	//czy�ci zestaw klock�w
	void wyczyscZestaw(){ l_klockow = 0; };
	//dodaje do zestawu klocek podany w argumencie funkcji
	void dodajKlocek(klocek k);
	//podaje liczb� klock�w
	int podajLiczbeKl(){ return l_klockow; };
	friend class gracz;
};