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
			menu_wybor = menuGlowne();		//menu g��wne
			if (menu_wybor == 3){			//je�li wybrano 3. opcj�, pokazuje informacje o grze, a p�niej wraca do menu g��wnego
				system("cls");
				info();
				system("PAUSE");
			}
			else if (menu_wybor == 4){
				system("cls");
				odczytajWyniki("wyniki.txt");
				system("PAUSE");
			}
			else if (menu_wybor == 0){		//je�li wybrano 0. opcj�, wychodzi z gry
				system("PAUSE");
				return 0;
			}
		} while (menu_wybor == 3 || menu_wybor == 4);	//p�tla wykonuje si� dop�ki wybierana jest 3. lub 4. opcja (czyli przy wybraniu nowej gry, b�d� wczytaniu gry, wychodzi)
		int lPktWybor;						//zmienna do przechowywania limitu punkt�w
		if (menu_wybor == 1 || menu_wybor == 2){	//je�li wybrano now� gr�, lub wczytano gr�
			int tmp;
			if (menu_wybor == 2){					//je�li wczytywana jest gra, wi�kszo�� danych jest od razu ustalonych
				if (wczytajGre(z, p, nr1, nr2, kolejnosc, lPktWybor, tmp) == false){
					z.wypelnijKlockami();
					menu_wybor = 1;
				}
			}
			if (menu_wybor == 1){					//je�li wybrano now� gr�, dane s� ustalane przez u�ytkownika
				do{
					system("cls");
					tmp = subMenu();			//menu do wyboru czy gra ma by� z komputerem
					if (tmp == 0){				//je�li wybrano opcj� 0, wraca do menu g��wnego
						break;
					}
					system("cls");
					lPktWybor = limitPunktow(imie1, imie2, tmp);	//menu do wyboru imion graczy i limitu punkt�w (zmienna lPktWybor)
				} while (lPktWybor == 0); //je�li wybrano opcj� 0, wraca do poprzedniego menu
			}
			bool koniec_rundy;				//flaga oznaczaj�ca, czy nast�pi� koniec rundy
			do{
				if (tmp == 0){
					break;
				}
				koniec_rundy = false;
				tab[0] = new gracz_uzytkownik(imie1);		//zastosowanie polimorfizmu
				if (menu_wybor == 2){						//je�li gra jest wczytywana, dane tymczasowe obiektu gracz s� przypisywane do gracza
					*(tab[0]) = nr1;
					nr1.usunBezOddania();
				}
				if (tmp == 2){
					tab[1] = new gracz_uzytkownik(imie2);		//dodawanie nowych graczy
					if (menu_wybor == 2){						//je�li gra jest wczytywana, dane tymczasowe obiektu gracz s� przypisywane do gracza
						*(tab[1]) = nr2;
						nr2.usunBezOddania();
					}
				}
				else if (tmp == 1){
					tab[1] = new gracz_komputer();
					if (menu_wybor == 2){						//je�li gra jest wczytywana, dane tymczasowe obiektu gracz s� przypisywane do gracza
						*(tab[1]) = nr2;
					}
				}
				int licznik = 0;							//zmienna pomocnicza przy sprawdzaniu, czy da si� jeszcze doda� klocki na plansz�
				if (menu_wybor == 1){
					p.wyczyscPlansze(z);						//czyszczenie planszy, je�li nie jest pusta
					tab[0]->oddajKlocki(z);						//po utworzeniu obiekt�w za pomoc� konstruktora jest im przyznawane 7 klock�w (0,0) - trzeba te klocki usun��
					tab[1]->oddajKlocki(z);
					kolejnosc = rand() % 2;						//wybierana jest losowa kolejno��
					ktoPierwszyLosuje(*(tab[0]), *(tab[1]), kolejnosc, z);
				}
				bool end1 = false;
				do{
					system("cls");
					cout << "Kolej gracza: " << tab[kolejnosc % 2]->podajImie() << " Liczba punktow: " << tab[kolejnosc % 2]->podajPunkty() << endl;
					cout << "Plansza:" << endl;
					p.wypiszKlocki();
					tab[kolejnosc % 2]->wypiszKlocki();
					if (kolejnosc % 2 == 0 || tmp == 2){		//je�li jest kolej u�ytkownika
						cout << "0. Wyjdz z gry." << endl;
						cout << "-1. Wylosuj dodatkowy klocek." << endl;
						cout << "-2. Zapisz gre." << endl;
						wybor = kontrolaPopr(-2, tab[kolejnosc % 2]->podajLiczbe());
						if (wybor == -1){						//je�li jest losowany kolejny klocek
							if (z.podajLiczbeKl() != 0){
								tab[kolejnosc % 2]->losujKlocki(z, 1);	//je�li w zestawie zosta�y klocki, to gracz dostaje dodatkowy
							}
							else{								//w przeciwnym wypadku zmienia si� kolej gracza
								licznik++;
								if (licznik != 2){
									cout << "Brak kart, oddajesz kolejke!" << endl;
								}
								else{
									zeroKartWTalii(*(tab[kolejnosc % 2]), *(tab[(kolejnosc + 1) % 2]));	//je�li w zestawie nie ma klock�w, losowane s� od nowa (wybierany jest zwyci�zca rundy)
									if (tab[kolejnosc%2]->podajPunkty() >= lPktWybor || tab[(kolejnosc+1)%2]->podajPunkty()>=lPktWybor){	//je�li gracz zdoby� wi�cej (lub tyle samo co limit pkt), wygrywa gr�
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
						if (wybor != 0){					//je�li wybrany jest nr kalocka
							if (gdzieWstawicKlocek(p, *(tab[kolejnosc % 2]), wybor) == false){		//je�li nie da si� tego klocka po�o�y�, mo�na wybra� jeszcze raz
								system("PAUSE");
								continue;
							}
							licznik = 0;
							if (dodawaniePunktow(*(tab[kolejnosc % 2]), p) >= lPktWybor){			//je�li gracz zdoby� wi�cej (lub tyle samo co limit pkt), wygrywa gr�
								cout << "Gracz " << tab[kolejnosc % 2]->podajImie() << " wygrywa, zdobywa " << tab[kolejnosc % 2]->podajPunkty() << " punktow!" << endl;
								zapiszWynik(*(tab[kolejnosc % 2]), *(tab[(kolejnosc + 1) % 2]), "wyniki.txt");
								system("PAUSE");
								break;
							}
						}
						if (wybor == 0){
							break;							//je�li wybrano 0, wychodzi do menu
						}
						if (tab[kolejnosc % 2]->podajLiczbe() == 0){
							zeroKart(*(tab[kolejnosc % 2]), *(tab[(kolejnosc + 1) % 2]));			//je�li gracz po�o�y� sw�j ostatni klocek, wygrywa rund�
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
					
					else if (tmp == 1 && kolejnosc % 2 == 1){										//je�li graczem jest komputer
						wybor = 1;
						int i;
						end1 = false;														//flaga ko�cz�ca
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
										zeroKart(*(tab[kolejnosc % 2]), *(tab[(kolejnosc + 1) % 2]));			//je�li gracz po�o�y� sw�j ostatni klocek, wygrywa rund�
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
										zeroKartWTalii(*(tab[kolejnosc % 2]), *(tab[(kolejnosc + 1) % 2]));	//je�li w zestawie nie ma klock�w, losowane s� od nowa (wybierany jest zwyci�zca rundy)
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
					tab[kolejnosc % 2]->oddajKlocki(z);	//oddawanie klock�w do zestawu
					tab[(kolejnosc + 1) % 2]->oddajKlocki(z);
					delete tab[0];				//usuni�cie obiektu alokowanego dynamicznie
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