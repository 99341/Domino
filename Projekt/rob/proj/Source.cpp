#include "Klocki.h"
#include "Gracz.h"
#include "Plansza.h"
#include "Menu.h"
#include <cstdlib>
#include <ctime>
#include <cmath>
#define MAX 100
using namespace std;

int main(){
	srand(time(NULL));
	int wybor;
	zestaw z;
	gracz* tab[2];			//2 graczy w grze
	gracz nr1, nr2;			//tymczasowe obiekty gracz; do wczytywania gry
	string imie1, imie2;
	plansza p;
	int kolejnosc;
	int menu_wybor;
	do{
		do{	
			system("cls");
			menu_wybor = menuGlowne();		//menu g³ówne
			if (menu_wybor == 3){			//jeœli wybrano 3. opcjê, pokazuje informacje o grze, a póŸniej wraca do menu g³ównego
				system("cls");
				info();
				system("PAUSE");
			}
			else if (menu_wybor == 4){
				system("cls");
				odczytajWyniki("wyniki.txt");
				system("PAUSE");
			}
			else if (menu_wybor == 0){		//jeœli wybrano 0. opcjê, wychodzi z gry
				system("PAUSE");
				return 0;
			}
		} while (menu_wybor == 3 || menu_wybor == 4);	//pêtla wykonuje siê dopóki wybierana jest 3. lub 4. opcja (czyli przy wybraniu nowej gry, b¹dŸ wczytaniu gry, wychodzi)
		int lPktWybor;						//zmienna do przechowywania limitu punktów
		if (menu_wybor == 1 || menu_wybor == 2){	//jeœli wybrano now¹ grê, lub wczytano grê
			int tmp;
			if (menu_wybor == 2){					//jeœli wczytywana jest gra, wiêkszoœæ danych jest od razu ustalonych
				if (wczytajGre(z, p, nr1, nr2, kolejnosc, lPktWybor, tmp) == false){
					z.wypelnijKlockami();
					menu_wybor = 1;
				}
			}
			if (menu_wybor == 1){					//jeœli wybrano now¹ grê, dane s¹ ustalane przez u¿ytkownika
				do{
					system("cls");
					tmp = subMenu();			//menu do wyboru czy gra ma byæ z komputerem
					if (tmp == 0){				//jeœli wybrano opcjê 0, wraca do menu g³ównego
						break;
					}
					system("cls");
					lPktWybor = limitPunktow(imie1, imie2, tmp);	//menu do wyboru imion graczy i limitu punktów (zmienna lPktWybor)
				} while (lPktWybor == 0); //jeœli wybrano opcjê 0, wraca do poprzedniego menu
			}
			bool koniec_rundy;				//flaga oznaczaj¹ca, czy nast¹pi³ koniec rundy
			do{
				if (tmp == 0){
					break;
				}
				koniec_rundy = false;
				tab[0] = new gracz_uzytkownik(imie1);		//zastosowanie polimorfizmu
				if (menu_wybor == 2){						//jeœli gra jest wczytywana, dane tymczasowe obiektu gracz s¹ przypisywane do gracza
					*(tab[0]) = nr1;
					nr1.usunBezOddania();
				}
				if (tmp == 2){
					tab[1] = new gracz_uzytkownik(imie2);		//dodawanie nowych graczy
					if (menu_wybor == 2){						//jeœli gra jest wczytywana, dane tymczasowe obiektu gracz s¹ przypisywane do gracza
						*(tab[1]) = nr2;
						nr2.usunBezOddania();
					}
				}
				else if (tmp == 1){
					tab[1] = new gracz_komputer();
					if (menu_wybor == 2){						//jeœli gra jest wczytywana, dane tymczasowe obiektu gracz s¹ przypisywane do gracza
						*(tab[1]) = nr2;
					}
				}
				int licznik = 0;							//zmienna pomocnicza przy sprawdzaniu, czy da siê jeszcze dodaæ klocki na planszê
				if (menu_wybor == 1){
					p.wyczyscPlansze(z);						//czyszczenie planszy, jeœli nie jest pusta
					tab[0]->oddajKlocki(z);						//po utworzeniu obiektów za pomoc¹ konstruktora jest im przyznawane 7 klocków (0,0) - trzeba te klocki usun¹æ
					tab[1]->oddajKlocki(z);
					kolejnosc = rand() % 2;						//wybierana jest losowa kolejnoœæ
					ktoPierwszyLosuje(*(tab[0]), *(tab[1]), kolejnosc, z);
				}
				bool end1 = false;
				do{
					system("cls");
					cout << "Kolej gracza: " << tab[kolejnosc % 2]->podajImie() << " Liczba punktow: " << tab[kolejnosc % 2]->podajPunkty() << endl;
					cout << "Plansza:" << endl;
					p.wypiszKlocki();
					tab[kolejnosc % 2]->wypiszKlocki();
					if (kolejnosc % 2 == 0 || tmp == 2){		//jeœli jest kolej u¿ytkownika
						cout << "0. Wyjdz z gry." << endl;
						cout << "-1. Wylosuj dodatkowy klocek." << endl;
						cout << "-2. Zapisz gre." << endl;
						wybor = kontrolaPopr(-2, tab[kolejnosc % 2]->podajLiczbe());
						if (wybor == -1){						//jeœli jest losowany kolejny klocek
							if (z.podajLiczbeKl() != 0){
								tab[kolejnosc % 2]->losujKlocki(z, 1);	//jeœli w zestawie zosta³y klocki, to gracz dostaje dodatkowy
							}
							else{								//w przeciwnym wypadku zmienia siê kolej gracza
								licznik++;
								if (licznik != 2){
									cout << "Brak kart, oddajesz kolejke!" << endl;
								}
								else{
									zeroKartWTalii(*(tab[kolejnosc % 2]), *(tab[(kolejnosc + 1) % 2]));	//jeœli w zestawie nie ma klocków, losowane s¹ od nowa (wybierany jest zwyciêzca rundy)
									if (tab[kolejnosc%2]->podajPunkty() >= lPktWybor || tab[(kolejnosc+1)%2]->podajPunkty()>=lPktWybor){	//jeœli gracz zdoby³ wiêcej (lub tyle samo co limit pkt), wygrywa grê
										ktoWygral(*(tab[kolejnosc % 2]), *(tab[(kolejnosc + 1) % 2]));
										zapiszWynik(*(tab[kolejnosc % 2]), *(tab[(kolejnosc + 1) % 2]), "wyniki.txt");
										system("PAUSE");
										break;
									}
									p.wyczyscPlansze(z);
									tab[0]->oddajKlocki(z);
									tab[1]->oddajKlocki(z);
									ktoPierwszyLosuje(*(tab[kolejnosc % 2]), *(tab[(kolejnosc + 1) % 2]), kolejnosc, z);
								}
								system("PAUSE");
								kolejnosc++;
							}
							continue;
						}
						else if (wybor == -2){
							zapiszGre(z, p, *(tab[0]), *(tab[1]), kolejnosc % 2, lPktWybor, tmp);	//zapisuje stan gry
							cout << "Zapisano gre!" << endl;
							system("PAUSE");
							continue;
						}
						if (wybor != 0){					//jeœli wybrany jest nr kalocka
							if (gdzieWstawicKlocek(p, *(tab[kolejnosc % 2]), wybor) == false){		//jeœli nie da siê tego klocka po³o¿yæ, mo¿na wybraæ jeszcze raz
								system("PAUSE");
								continue;
							}
							licznik = 0;
							if (dodawaniePunktow(*(tab[kolejnosc % 2]), p) >= lPktWybor){			//jeœli gracz zdoby³ wiêcej (lub tyle samo co limit pkt), wygrywa grê
								cout << "Gracz " << tab[kolejnosc % 2]->podajImie() << " wygrywa, zdobywa " << tab[kolejnosc % 2]->podajPunkty() << " punktow!" << endl;
								zapiszWynik(*(tab[kolejnosc % 2]), *(tab[(kolejnosc + 1) % 2]), "wyniki.txt");
								system("PAUSE");
								break;
							}
						}
						if (wybor == 0){
							break;							//jeœli wybrano 0, wychodzi do menu
						}
						if (tab[kolejnosc % 2]->podajLiczbe() == 0){
							zeroKart(*(tab[kolejnosc % 2]), *(tab[(kolejnosc + 1) % 2]));			//jeœli gracz po³o¿y³ swój ostatni klocek, wygrywa rundê
							p.wyczyscPlansze(z);
							tab[0]->oddajKlocki(z);
							tab[1]->oddajKlocki(z);
							if (tab[kolejnosc % 2]->podajPunkty() >= lPktWybor){
								cout << "Gracz " << tab[kolejnosc % 2]->podajImie() << " wygrywa, zdobywa " << tab[kolejnosc % 2]->podajPunkty() << " punktow!" << endl;
								zapiszWynik(*(tab[kolejnosc % 2]), *(tab[(kolejnosc + 1) % 2]), "wyniki.txt");
								system("PAUSE");
								break;
							}
							ktoPierwszyLosuje(*(tab[0]), *(tab[1]), kolejnosc, z);
							system("PAUSE");
						}
						kolejnosc++;
					}
					
					else if (tmp == 1 && kolejnosc % 2 == 1){										//jeœli graczem jest komputer
						wybor = 1;
						int i;
						end1 = false;														//flaga koñcz¹ca
						while (tab[kolejnosc%2]->podajPunkty()<lPktWybor){
							int stara_liczba = tab[kolejnosc % 2]->podajLiczbe();
							for (i = 0; i < stara_liczba; i++){
								if (gdzieWstawicKlocekKomputer(p, *(tab[kolejnosc % 2]), ((rand() % stara_liczba) + 1)) == true){
									licznik = 0;
									if (dodawaniePunktow(*(tab[kolejnosc % 2]), p) >= lPktWybor){
										cout << "Komputer wygrywa, zdobywa " << tab[kolejnosc % 2]->podajPunkty() << " punktow!" << endl;
										zapiszWynik(*(tab[kolejnosc % 2]), *(tab[(kolejnosc + 1) % 2]), "wyniki.txt");
										end1 = true;
									}
									if (tab[kolejnosc % 2]->podajLiczbe() == 0){
										zeroKart(*(tab[kolejnosc % 2]), *(tab[(kolejnosc + 1) % 2]));			//jeœli gracz po³o¿y³ swój ostatni klocek, wygrywa rundê
										p.wyczyscPlansze(z);
										tab[0]->oddajKlocki(z);
										tab[1]->oddajKlocki(z);
										ktoPierwszyLosuje(*(tab[0]), *(tab[1]), kolejnosc, z);
									}
									kolejnosc++;
									system("PAUSE");
									break;
								}
							}
							if (i != stara_liczba){
								break;
							}
							if (end1 == true){
								break;
							}
							if (stara_liczba == tab[kolejnosc % 2]->podajLiczbe()){
								if (z.podajLiczbeKl() != 0){
									tab[kolejnosc % 2]->losujKlocki(z, 1);
								}
								else{
									licznik++;
									if (licznik != 2){
										cout << "Brak kart, komputer oddaje kolejke!" << endl;
									}
									else{
										zeroKartWTalii(*(tab[kolejnosc % 2]), *(tab[(kolejnosc + 1) % 2]));	//jeœli w zestawie nie ma klocków, losowane s¹ od nowa (wybierany jest zwyciêzca rundy)
										if (tab[kolejnosc % 2]->podajPunkty() >= lPktWybor || tab[(kolejnosc + 1) % 2]->podajPunkty() >= lPktWybor){
											ktoWygral(*(tab[kolejnosc % 2]), *(tab[(kolejnosc + 1) % 2]));
											zapiszWynik(*(tab[kolejnosc % 2]), *(tab[(kolejnosc + 1) % 2]), "wyniki.txt");
											end1 = true;
										}
										p.wyczyscPlansze(z);
										tab[0]->oddajKlocki(z);
										tab[1]->oddajKlocki(z);
										ktoPierwszyLosuje(*(tab[kolejnosc % 2]), *(tab[(kolejnosc + 1) % 2]), kolejnosc, z);
									}
									system("PAUSE");
									kolejnosc++;
									break;
								}
							}
							else{
								break;
							}
						}
						if (end1 == true){
							break;
						}
					}
				} while (wybor != 0);
				if (wybor == 0 || end1 == true){
					p.wyczyscPlansze(z);		//czyszczenie planszy
					koniec_rundy = true;
					tab[kolejnosc % 2]->oddajKlocki(z);	//oddawanie klocków do zestawu
					tab[(kolejnosc + 1) % 2]->oddajKlocki(z);
					delete tab[0];				//usuniêcie obiektu alokowanego dynamicznie
					delete tab[1];
				}
				if (tab[0]->podajPunkty() >= lPktWybor || tab[1]->podajPunkty() >= lPktWybor){
					koniec_rundy = true;
					tab[kolejnosc % 2]->oddajKlocki(z);
					tab[(kolejnosc + 1) % 2]->oddajKlocki(z);
					delete tab[0];
					delete tab[1];
				}
			} while (koniec_rundy == false);
		}
	} while (true);
	return 0;
}