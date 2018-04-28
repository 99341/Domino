#include "Plansza.h"

klocek plansza::dodajOdLewej(klocek k){
	if (l_klockow == 0){
		return dodajOdPrawej(k);
	}
	else if (l_klockow > 0 && l_klockow < 28){
		for (int i = l_klockow-1; i >=0; i--){
			lista[i + 1] = lista[i];
		}
		lista[0] = k;
		l_klockow++;
		return k;
	}
	return k;
}

klocek plansza::dodajOdPrawej(klocek k){
	if (l_klockow < 28){
		lista[l_klockow] = k;
		l_klockow++;
	}
	return k;
}

void plansza::wypiszKlocki(){
	for (int i = 0; i < l_klockow; i++){
		cout << "|" << lista[i].podajPierwsza() << "|" << lista[i].podajDruga() << "|";
	}
	cout << endl;
}

klocek plansza::podajLewy(){
	if (l_klockow>0){
		return lista[0];
	}
	return klocek(-1, -1);
}

klocek plansza::podajPrawy(){
	if (l_klockow > 0){
		return lista[l_klockow - 1];
	}
	return klocek(-1, -1);
}

klocek plansza::usunKlocek(int nr){
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
	return klocek(-1, -1);
}

void plansza::wyczyscPlansze(zestaw& z){
	for (int i = 0; i < l_klockow; i){
		z.dodajKlocek(usunKlocek(i + 1));
	}
}

klocek plansza::sprawdzOdLewejIWstaw(klocek k){
	if (podajLewy().podajPierwsza() == -1){
		return dodajOdLewej(k);
	}
	if (k.podajDruga() == podajLewy().podajPierwsza()){
		return dodajOdLewej(k);
	}
	else if (k.podajPierwsza() == podajLewy().podajPierwsza()){
		k.odwrocKolejnosc();
		return dodajOdLewej(k);
	}
	cout << "Nie mozna dodac tego klocka!" << endl;
	system("PAUSE");
	return klocek(-1, -1);
}

klocek plansza::sprawdzOdPrawejIWstaw(klocek k){
	if (podajLewy().podajPierwsza() == -1){
		return dodajOdLewej(k);
	}
	if (k.podajPierwsza() == podajPrawy().podajDruga()){
		return dodajOdPrawej(k);
	}
	else if (k.podajDruga() == podajPrawy().podajDruga()){
		k.odwrocKolejnosc();
		return dodajOdPrawej(k);
	}
	cout << "Nie mozna dodac tego klocka!" << endl;
	system("PAUSE");
	return klocek(-1, -1);
}

bool plansza::sprawdzOdLewej(klocek k){
	if (l_klockow == 0){
		return true;
	}
	else if (k.podajDruga() == podajLewy().podajPierwsza()){
		return true;
	}
	else if (k.podajPierwsza() == podajLewy().podajPierwsza()){
		return true;
	}
	return false;
}

bool plansza::sprawdzOdPrawej(klocek k){
	if (l_klockow == 0){
		return true;
	}
	else if (k.podajPierwsza() == podajPrawy().podajDruga()){
		return true;
	}
	else if (k.podajDruga() == podajPrawy().podajDruga()){
		return true;
	}
	return false;
}

klocek plansza::podajKlocek(int nr){
	return lista[nr - 1];
}