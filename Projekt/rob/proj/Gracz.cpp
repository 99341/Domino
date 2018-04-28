#include "Gracz.h"
#include "Menu.h"
#include <cstdlib>

void gracz::losujKlocki(zestaw &z){
	int indeks;
	for (int i = 0; i < l_klockow; i++){
		indeks = rand() % (z.podajLiczbeKl())+1;
		lista[i] = z.podajKlocek(indeks);
		z.usunKlocek(indeks);
	}
}

void gracz::losujKlocki(zestaw &z, int liczba){
	if (liczba > 7 || liczba < 0){
		liczba = 7;
	}
	for (int i = l_klockow; i < l_klockow+liczba; i++){
		lista[i] = z.podajKlocek((rand() % z.podajLiczbeKl())+1);
		z.usunKlocek(lista[i]);
	}
	l_klockow += liczba;
}

void gracz::wypiszKlocki(){
	cout << "Klocki gracza:" << endl;
	for (int i = 1; i <= l_klockow; i++){
		cout << i << ". |" << lista[i-1].podajPierwsza() << "|" << lista[i-1].podajDruga() << "|" << endl;
	}
}

void gracz::wypiszKlocek(int nr){
	if (nr<=l_klockow && nr>0)
		cout << nr << ". |" << lista[nr-1].podajPierwsza() << "|" << lista[nr-1].podajDruga() << "|" << endl;
}

klocek gracz::usunKlocek(int nr){
	if (nr > 0 && nr<=l_klockow){
		klocek tmp;				//klocek, który bêdzie zwrócony przez funkcjê
		if (l_klockow > 1 && nr != l_klockow){
			tmp = lista[nr - 1];
			for (int i = nr - 1; i < l_klockow - 1; i++){
				lista[i] = lista[i + 1];
			}
			l_klockow--;
		}
		else if (l_klockow == 1 || nr == l_klockow){
			tmp = lista[nr - 1];
			l_klockow--;
		}
		return tmp;
	}
}

klocek gracz::podajKlocek(int nr){
	if (nr > 0 && nr <= l_klockow){
		return lista[nr - 1];
	}
	return klocek(-1, -1);
}

klocek gracz::dodajKlocek(klocek k){
	if (l_klockow < 7){
		lista[l_klockow] = k;
		l_klockow++;
	}
	return k;
}

void gracz::polozOdLewej(plansza& p, int nr){
	if (p.sprawdzOdLewejIWstaw(podajKlocek(nr)).podajPierwsza() != -1){
		usunKlocek(nr);
	}
}

void gracz::polozOdPrawej(plansza& p, int nr){
	if (p.sprawdzOdPrawejIWstaw(podajKlocek(nr)).podajPierwsza() != -1){
		usunKlocek(nr);
	}
}

void gracz::oddajKlocki(zestaw& z){
	for (int i = 0; i < l_klockow; i){
		z.dodajKlocek(usunKlocek(i + 1));
	}
}

void gracz_komputer::wypiszKlocki(){
	return;
}

void gracz_komputer::wypiszKlocek(int nr){
	return;
}

void gracz::usunBezOddania(){
	l_klockow = 0;
}

