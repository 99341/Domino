#pragma once
#include <iostream>
using namespace std;

class klocek{
	int pierwsza_l;		//pierwsza liczba oczek
	int druga_l;		//druga liczba oczek
public:
	klocek() :pierwsza_l(0), druga_l(0){};
	klocek(int a, int b) :pierwsza_l(a), druga_l(b){};
	//zmienia pierwsz¹ liczbê oczek
	void zmienPierwsza(int a){ pierwsza_l = a; };
	//zmienia drug¹ liczbê oczek
	void zmienDruga(int b){ druga_l = b; };
	//podaje pierwsz¹ liczbê oczek
	int podajPierwsza(){ return pierwsza_l; };
	//podaje drug¹ liczbê oczek
	int podajDruga(){ return druga_l; };
	//odwraca kolejnoœæ cyfr w domino, domyœlnie pierwsza cyfra nie mo¿e byæ wiêksza od drugiej
	void odwrocKolejnosc();		
	//przeci¹¿ony operator porównania, sprawdza, czy drugi klocek jest taki sam
	bool operator==(const klocek& k);
	//metoda sprawdza, czy klocek jest dublem
	bool czyJestDublem() { return pierwsza_l == druga_l; };
	//przeci¹¿ony operator przypisania, kopiuje wartoœci z klocka po prawej do lewego
	klocek& operator=(const klocek& k){
		pierwsza_l = k.pierwsza_l;
		druga_l = k.druga_l;
		return *this;
	}
};

class zestaw{
	klocek klocki[28];	//zestaw klocków
	int l_klockow;
public:
	zestaw();
	//wype³nia zestaw na nowo klockami
	void wypelnijKlockami();
	//wypisuje ca³y zestaw klocków
	void wypiszZestaw();
	//wypisuje pojedynczy klocek
	void wypiszKlocek(int nr);
	//zwraca pojedynczy klocek
	klocek podajKlocek(int nr);
	//usuwa klocek o danym numerze
	klocek usunKlocek(int nr);
	//usuwa klocek podany jako argument
	klocek usunKlocek(klocek k);
	//czyœci zestaw klocków
	void wyczyscZestaw(){ l_klockow = 0; };
	//dodaje do zestawu klocek podany w argumencie funkcji
	void dodajKlocek(klocek k);
	//podaje liczbê klocków
	int podajLiczbeKl(){ return l_klockow; };
	friend class gracz;
};