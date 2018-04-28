#pragma once
#include "klocki.h"
#include "Plansza.h"
#include <ctime>
#include <string>

class gracz{
protected:
	klocek lista[28];	//zestaw klock�w (max 7, chyba �e gracz musi losowa� dodatkowe klocki)
	int l_klockow;		//liczba klock�w, kt�re posiada aktualnie gracz
	int punkty;			//liczba punkt�w, kt�re zdoby� w trakcie rundy
	string imie;		//imie gracza
public:
	gracz(){ l_klockow = 0; punkty = 0; imie = "Abc"; };
	gracz(string i, int klocki = 0, int pkt = 0){
		if (klocki > 7 || klocki < 0){
			l_klockow = 0;
		}
		else{
			l_klockow = klocki;
		}
		if (punkty < 0){
			punkty = 0;
		}
		else{
			punkty = pkt;
		}
		imie = i;
	};
	//metoda losuje z zestawu liczb� klock�w ustalon� w konstruktorze
	void losujKlocki(zestaw &lista);
	//metoda losuje z zestawu podan� liczb� klock�w
	void losujKlocki(zestaw &lista, int liczba);
	//metoda wirtualna, wypisanie klock�w gracza
	virtual void wypiszKlocki();								
	//wypisanie pojedynczego klocka o podanym numerze
	void wypiszKlocek(int nr);
	//usuni�cie klocka o podanym numerze
	klocek usunKlocek(int nr);
	//zwr�cenie klocka o podanym numerze
	klocek podajKlocek(int nr);
	//dodanie klocka o podanej liczbie oczek
	void dodajKlocek(int a, int b);
	//dodanie gotowego obiektu klocek
	klocek dodajKlocek(klocek k);
	//oddanie klock�w do zestawu
	void oddajKlocki(zestaw& z);
	//po�o�enie klocka na planszy od lewej strony
	void polozOdLewej(plansza& p, int nr);
	//po�o�enie klocka na planszy od prawej strony
	void polozOdPrawej(plansza& p, int nr);
	//metoda zwraca liczb� klock�w
	int podajLiczbe(){ return l_klockow; };
	//metoda zwraca liczb� punkt�w
	int podajPunkty() { return punkty; };
	//dodaje podan� liczb� punkt�w do puli z punktami
	void dodajDoPunktow(int pkt) { punkty += pkt; };
	//metoda zwraca imi� gracza
	string podajImie(){ return imie; };
	//metoda ustawia nowe imi�
	void zmienImie(string i){ imie = i; };
	//zmienia liczb� punkt�w gracza na 0
	void zerujPunkty(){ punkty = 0; };
	//usuwa klocki gracza bez oddawania ich do zestawu
	void usunBezOddania();										
};

class gracz_uzytkownik : public gracz{
public:
	gracz_uzytkownik() :gracz("Uzytkownik"){};
	gracz_uzytkownik(string i, int klocki = 0, int pkt = 0) :gracz(i, klocki, pkt){};
	//przeci��ony operator przypisania, kopiuje klocki, imi� i punkty z obiektu po prawej
	gracz_uzytkownik& operator=(gracz& g){
		l_klockow = g.podajLiczbe();
		for (int i = 0; i < g.podajLiczbe(); i++){
			lista[i] = g.podajKlocek(i+1);
		}
		punkty = g.podajPunkty();
		imie = g.podajImie();
		return *this;
	}
};

class gracz_komputer : public gracz{
public:
	gracz_komputer() :gracz("Komputer"){};
	gracz_komputer(int klocki, int pkt) :gracz("Komputer", klocki, pkt){};
	//instancja metody wirtualnej
	void wypiszKlocki();
	void wypiszKlocek(int nr);
	//przeci��ony operator przypisania, kopiuje klocki, imi� i punkty z obiektu po prawej
	gracz_komputer& operator=(gracz& g){
		l_klockow = g.podajLiczbe();
		for (int i = 0; i < g.podajLiczbe(); i++){
			lista[i] = g.podajKlocek(i + 1);
		}
		punkty = g.podajPunkty();
		return *this;
	}
};