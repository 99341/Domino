#include "Klocki.h"

void klocek::odwrocKolejnosc(){
	int tmp = podajPierwsza();
	zmienPierwsza(podajDruga());
	zmienDruga(tmp);
}

bool klocek::operator==(const klocek& k){
	if (pierwsza_l == k.pierwsza_l){
		if (druga_l == k.druga_l){
			return true;
		}
	}
	return false;
}

zestaw::zestaw(){
	int i = 0, j, k;
	l_klockow = 28;
	for (j = 0; j < 7; j++){
		for (k = 0; k < 7; k++){
			if (k == 0){
				k = j;
			}
			klocki[i].zmienPierwsza(j);
			klocki[i].zmienDruga(k);
			i++;
		}
	}
}

void zestaw::wypelnijKlockami(){
	int i = 0, j, k;
	l_klockow = 28;
	for (j = 0; j < 7; j++){
		for (k = 0; k < 7; k++){
			if (k == 0){
				k = j;
			}
			klocki[i].zmienPierwsza(j);
			klocki[i].zmienDruga(k);
			i++;
		}
	}
}

void zestaw::wypiszZestaw(){
	for (int i = 0; i < l_klockow; i++){
		cout << "|" << klocki[i].podajPierwsza() << "|" << klocki[i].podajDruga() << "|";
	}
	cout << endl;
}

void zestaw::wypiszKlocek(int nr){
	cout << "|" << klocki[nr-1].podajPierwsza() << "|" << klocki[nr-1].podajDruga() << "|";
}

klocek zestaw::podajKlocek(int nr){
	return klocki[nr - 1];
}

klocek zestaw::usunKlocek(int nr){
	if (nr > 0 && nr<=l_klockow){
		klocek tmp;				//klocek, który bêdzie zwrócony przez funkcjê
		if (l_klockow > 1 && nr!=l_klockow){
			tmp = klocki[nr - 1];
			for (int i = nr - 1; i < l_klockow - 1; i++){
				klocki[i] = klocki[i + 1];
			}
			l_klockow--;
		}
		else if (l_klockow == 1 || nr == l_klockow){
			tmp = klocki[nr - 1];
			l_klockow--;
		}
		return tmp;
	}
}

klocek zestaw::usunKlocek(klocek k){
	for (int i = 0; i < l_klockow; i++){
		if (k.podajPierwsza() == klocki[i].podajPierwsza()){
			if (k.podajDruga() == klocki[i].podajDruga()){
				usunKlocek(i + 1);
			}
		}
	}
	return k;
}

void zestaw::dodajKlocek(klocek k){
	if (l_klockow < 28){
		klocki[l_klockow] = k;
		l_klockow++;
	}
}
