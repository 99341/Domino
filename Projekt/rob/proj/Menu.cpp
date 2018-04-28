#include "Menu.h"

void ktoPierwszyLosuje(gracz& nr1, gracz& nr2, int kol, zestaw& z){
	if (kol == 0){
		nr1.losujKlocki(z, 7);
		nr2.losujKlocki(z, 7);
	}
	else{
		nr2.losujKlocki(z, 7);
		nr1.losujKlocki(z, 7);
	}
}

bool gdzieWstawicKlocek(plansza& p, gracz& g, int wybor){
	if (p.sprawdzOdLewej(g.podajKlocek(wybor)) == true){
		if (p.sprawdzOdPrawej(g.podajKlocek(wybor)) == true){
			int tmp;
			if (p.podajLiczbe() != 0){
				cout << "Wstawic ten klocek:" << endl;
				cout << "[1] Od lewej.\n[2] Od prawej." << endl;
				tmp = kontrolaPopr<int>(1, 2);
				switch (tmp){
				case 1:
					g.polozOdLewej(p, wybor);
					return true;
					break;
				case 2:
					g.polozOdPrawej(p, wybor);
					return true;
					break;
				default:
					break;
				}
			}
			else{
				g.polozOdPrawej(p, wybor);
				return true;
			}
		}
		else if (p.sprawdzOdPrawej(g.podajKlocek(wybor)) == false){
			g.polozOdLewej(p, wybor);
			return true;
		}
	}
	else if (p.sprawdzOdPrawej(g.podajKlocek(wybor)) == true){
		g.polozOdPrawej(p, wybor);
		return true;
	}
	else if (p.sprawdzOdPrawej(g.podajKlocek(wybor)) == false && p.sprawdzOdLewej(g.podajKlocek(wybor)) == false){
		cout << "Nie mozna postawic tego klocka!" << endl;
		return false;
	}
	return false;
}

bool gdzieWstawicKlocekKomputer(plansza& p, gracz& g, int wybor){
	if (p.sprawdzOdLewej(g.podajKlocek(wybor)) == true){
		if (p.sprawdzOdPrawej(g.podajKlocek(wybor)) == true){
			int tmp;
			if (p.podajLiczbe() != 0){
				tmp = (rand() % 2) + 1;
				switch (tmp){
				case 1:
					g.polozOdLewej(p, wybor);
					return true;
					break;
				case 2:
					g.polozOdPrawej(p, wybor);
					return true;
					break;
				default:
					break;
				}
			}
			else{
				g.polozOdPrawej(p, wybor);
				return true;
			}
		}
		else if (p.sprawdzOdPrawej(g.podajKlocek(wybor)) == false){
			g.polozOdLewej(p, wybor);
			return true;
		}
	}
	else if (p.sprawdzOdPrawej(g.podajKlocek(wybor)) == true){
		g.polozOdPrawej(p, wybor);
		return true;
	}
	else if (p.sprawdzOdPrawej(g.podajKlocek(wybor)) == false && p.sprawdzOdLewej(g.podajKlocek(wybor)) == false){
		return false;
	}
	return false;
}

int wielokrotnoscPiatki(int l_punktow){
	int v1 = 0, v2 = 5;
	for (int i = 0; v2 < l_punktow; i++){
		v1 += 5;
		v2 += 5;
	}
	int r1, r2;
	r1 = abs(l_punktow - v1);
	r2 = abs(v2 - l_punktow);
	if (r2 < r1){
		return v2;
	}
	return v1;
}

void zeroKart(gracz& zwyciezca, gracz& przegrany){
	cout << "Gracz " << zwyciezca.podajImie() << " konczy runde!" << endl;
	int liczba_pkt = 0;
	for (int i = 0; i < przegrany.podajLiczbe(); i++){
		liczba_pkt += przegrany.podajKlocek(i + 1).podajPierwsza();
		liczba_pkt += przegrany.podajKlocek(i + 1).podajDruga();
	}
	if ((liczba_pkt % 5) != 0){
		liczba_pkt = wielokrotnoscPiatki(liczba_pkt);
	}
	zwyciezca.dodajDoPunktow(liczba_pkt);
	cout << "Otrzymal lacznie " << zwyciezca.podajPunkty() << " punktow!" << endl;
	cout << "Gracz " << przegrany.podajImie() << ": " << przegrany.podajPunkty() << " punktow." << endl;
}

void zeroKartWTalii(gracz& nr1, gracz& nr2){
	cout << "Koniec klockow w zestawie, zaden gracz nie moze polozyc klocka na stole." << endl;
	int suma1=0, suma2=0;
	for (int i = 0; i < nr1.podajLiczbe(); i++){
		suma1 += nr1.podajKlocek(i + 1).podajPierwsza();
		suma1 += nr1.podajKlocek(i + 1).podajDruga();
	}
	for (int i = 0; i < nr2.podajLiczbe(); i++){
		suma2 += nr2.podajKlocek(i + 1).podajPierwsza();
		suma2 += nr2.podajKlocek(i + 1).podajDruga();
	}
	if (suma1 < suma2){
		nr1.dodajDoPunktow(wielokrotnoscPiatki(suma2 - suma1));
		cout << "Gracz " << nr1.podajImie() << " ma teraz lacznie " << nr1.podajPunkty() << " punktow!" << endl;
		cout << "Gracz " << nr2.podajImie() << ": " << nr2.podajPunkty() << " punktow." << endl;
	}
	else if (suma1>suma2){
		nr2.dodajDoPunktow(wielokrotnoscPiatki(suma1 - suma2));
		cout << "Gracz " << nr2.podajImie() << " ma teraz lacznie " << nr2.podajPunkty() << " punktow!" << endl;
		cout << "Gracz " << nr1.podajImie() << ": " << nr1.podajPunkty() << " punktow." << endl;
	}
}

int menuGlowne(){
	int wybor;
	cout << "[1] Nowa gra." << endl;
	cout << "[2] Wczytaj gre." << endl;
	cout << "[3] O grze." << endl;
	cout << "[4] Tablica wynikow." << endl;
	cout << "[0] Wyjdz." << endl;
	while (scanf_s("%d", &wybor) != 1 || wybor<0 || wybor>4 || getchar() != '\n'){
		cout << "Nie ma takiej opcji!" << endl;
		while (getchar() != '\n');
	}
	return wybor;
}

int subMenu(){
	int wybor;
	cout << "[1] Z komputerem." << endl;
	cout << "[2] Z drugim graczem." << endl;
	cout << "[0] Wroc." << endl;
	while (scanf_s("%d", &wybor) != 1 || wybor<0 || wybor>2 || getchar() != '\n'){
		cout << "Nie ma takiej opcji!" << endl;
		while (getchar() != '\n');
	}
	return wybor;
}

int limitPunktow(string& imie1, string& imie2, int formaGry){
	cout << "Wybierz imie pierwszego gracza: ";
	cin >> imie1;
	if (formaGry == 1){
		imie2 = "Komputer";
	}
	else{
		cout << "Wybierz imie drugiego gracza: ";
		cin >> imie2;
	}
	int wybor;
	cout << "Wybierz limit punktow w grze:" << endl;
	cout << "[1] 20." << endl;
	cout << "[2] 100." << endl;
	cout << "[3] 250." << endl;
	cout << "[4] 500." << endl;
	cout << "[0] Wroc." << endl;
	while (scanf_s("%d", &wybor) != 1 || wybor<0 || wybor>4 || getchar() != '\n'){
		cout << "Nie ma takiej opcji!" << endl;
		while (getchar() != '\n');
	}
	if (wybor == 1){
		return 20;
	}
	else if (wybor == 2){
		return 100;
	}
	else if (wybor == 3){
		return 250;
	}
	else if (wybor == 4){
		return 500;
	}
	return wybor;
}

void info(){
	cout << "Domino" << endl << endl;
	cout << "Gra polega na zdobyciu okreslonej z gory liczby punktow \npoprzez ukladanie klockow w taki sposob," << endl;
	cout << "aby strona dotykajaca nowego klocka miala taka sama liczbe oczek, \nco strona dotykajaca starego." << endl;
	cout << "Punkty sa naliczane, gdy: " << endl;
	cout << "- po polozeniu klocka suma oczek na koncach lancucha jest podzielna przez 5 \n(w przypadku dubli liczone sa 2 strony klocka)" << endl;
	cout << "- gracz wylozyl swoj ostatni klocek" << endl;
	cout << "- nie mozna juz wykladac klockow na plansze, a w zbiorze nie ma dodatkowych \nklockow." << endl;
	cout << "Autor programu: Przemyslaw Salega, 2017" << endl;
}

int dodawaniePunktow(gracz& g, plansza p){
	if (p.podajLewy() == p.podajPrawy()){	//gdy jest tylko jeden klocek na planszy
		if ((p.podajLewy().podajPierwsza() + p.podajLewy().podajDruga()) % 5 == 0){
			g.dodajDoPunktow(p.podajLewy().podajPierwsza() + p.podajLewy().podajDruga());
			return g.podajPunkty();
		}
	}
	if (!p.podajLewy().czyJestDublem() && !p.podajPrawy().czyJestDublem()){	//gdy lewy i prawy nie s¹ dublami
		if ((p.podajLewy().podajPierwsza() + p.podajPrawy().podajDruga()) % 5 == 0){
			g.dodajDoPunktow(p.podajLewy().podajPierwsza() + p.podajPrawy().podajDruga());
			return g.podajPunkty();
		}
	}
	if (p.podajLewy().czyJestDublem() && !p.podajPrawy().czyJestDublem()){	//gdy lewy jest dublem, a prawy nie
		if ((p.podajLewy().podajPierwsza() + p.podajLewy().podajDruga() + p.podajPrawy().podajDruga()) % 5 == 0){
			g.dodajDoPunktow(p.podajLewy().podajPierwsza() + p.podajLewy().podajDruga() + p.podajPrawy().podajDruga());
			return g.podajPunkty();
		}
	}
	if (!p.podajLewy().czyJestDublem() && p.podajPrawy().czyJestDublem()){	//gdy tylko prawy jest dublem
		if ((p.podajLewy().podajPierwsza() + p.podajPrawy().podajPierwsza() + p.podajPrawy().podajDruga()) % 5 == 0){
			g.dodajDoPunktow(p.podajLewy().podajPierwsza() + p.podajPrawy().podajPierwsza() + p.podajPrawy().podajDruga());
			return g.podajPunkty();
		}
	}
	if (p.podajLewy().czyJestDublem() && p.podajPrawy().czyJestDublem()){	//gdy oba s¹ dublami
		if ((p.podajLewy().podajPierwsza() + p.podajLewy().podajDruga() + p.podajPrawy().podajPierwsza() + p.podajPrawy().podajDruga()) % 5 == 0){
			g.dodajDoPunktow(p.podajLewy().podajPierwsza() + p.podajLewy().podajDruga() + p.podajPrawy().podajPierwsza() + p.podajPrawy().podajDruga());
			return g.podajPunkty();
		}
	}
	return g.podajPunkty();
}

void ktoWygral(gracz g1, gracz g2){
	if (g1.podajPunkty() >= g2.podajPunkty()){
		cout << "Gracz " << g1.podajImie() << " wygrywa, zdobywa " << g1.podajPunkty() << " punktow!" << endl;
	}
	else if (g1.podajPunkty() < g2.podajPunkty()){
		cout << "Gracz " << g2.podajImie() << " wygrywa, zdobywa " << g2.podajPunkty() << " punktow!" << endl;
	}
}

void zapiszWynik(gracz g1, gracz g2, string n_pliku){
	ofstream of;
	of.open(n_pliku, ios::app);
	of << g1.podajImie() << " " << g1.podajPunkty() << " " << g2.podajImie() << " " << g2.podajPunkty() << endl;
	of.close();
}

void odczytajWyniki(string n_pliku){
	string imie;
	int wynik;
	ifstream in;
	in.open(n_pliku, ios::in);
	if (!in.is_open()){
		cout << "Brak wynikow!" << endl;
	}
	else{
		cout << "Imie:\tWynik:\tImie:\tWynik:" << endl << endl;
		while (!in.eof()){
			in >> imie;
			if (in.eof()){
				break;
			}
			in >> wynik;
			cout << imie << "\t" << wynik << "\t";
			in >> imie;
			in >> wynik;
			cout << imie << "\t" << wynik << endl << endl;
		}
		in.close();
	}
}

void zapiszGre(zestaw z, plansza p, gracz nr1, gracz nr2, int kolejnosc, int limitPkt, int wybor){
	ofstream of;
	of.open("zestaw.txt", ios::out);			//zapisywanie klocków z zestawu
	for (int i = 0; i < z.podajLiczbeKl(); i++){
		of << z.podajKlocek(i + 1).podajPierwsza() << " " << z.podajKlocek(i + 1).podajDruga() << endl;
	}
	of.close();
	of.open("plansza.txt", ios::out);			//zapisywanie klocków z planszy
	for (int i = 0; i < p.podajLiczbe(); i++){
		of << p.podajKlocek(i + 1).podajPierwsza() << " " << p.podajKlocek(i + 1).podajDruga() << endl;
	}
	of.close();
	of.open("gracz1.txt", ios::out);			//zapisywanie danych 1. gracza (imiê, punkty, klocki)
	of << nr1.podajImie() << " " << nr1.podajPunkty() << endl;
	for (int i = 0; i < nr1.podajLiczbe(); i++){
		of << nr1.podajKlocek(i + 1).podajPierwsza() << " " << nr1.podajKlocek(i + 1).podajDruga() << endl;
	}
	of.close();
	of.open("gracz2.txt", ios::out);			//zapisywanie danych 2. gracza (imiê, punkty, komputer/gracz, klocki)
	of << nr2.podajImie() << " " << nr2.podajPunkty() << " " << wybor << endl;
	for (int i = 0; i < nr2.podajLiczbe(); i++){
		of << nr2.podajKlocek(i + 1).podajPierwsza() << " " << nr2.podajKlocek(i + 1).podajDruga() << endl;
	}
	of.close();
	of.open("daneGry.txt", ios::out);
	of << kolejnosc << endl << limitPkt;
	of.close();
}

bool wczytajGre(zestaw& z, plansza& p, gracz& nr1, gracz& nr2, int& kolejnosc, int& limitPkt, int& wybor){
	z.wyczyscZestaw();
	klocek k;
	int a, b;
	ifstream in;
	in.open("zestaw.txt", ios::in);				//wczytywanie zestawu
	if (!in.is_open()){
		cout << "Blad przy wczytywaniu gry!" << endl;
		system("PAUSE");
		return false;
	}
	int i = 0;
	while (!in.eof()){
		in >> a;
		if (in.eof()){
			break;
		}
		in >> b;
		if (in.fail()){
			cout << "Blad przy wczytywaniu gry!" << endl;
			system("PAUSE");
			return false;
		}
		k.zmienPierwsza(a);
		k.zmienDruga(b);
		z.dodajKlocek(k);
	}
	in.close();
	in.open("plansza.txt", ios::in);			//wczytywanie planszy
	if (!in.is_open()){
		cout << "Blad przy wczytywaniu gry!" << endl;
		system("PAUSE");
		return false;
	}
	while (!in.eof()){
		in >> a;
		if (in.eof()){
			break;
		}
		in >> b;
		if (in.fail()){
			cout << "Blad przy wczytywaniu gry!" << endl;
			system("PAUSE");
			return false;
		}
		k.zmienPierwsza(a);
		k.zmienDruga(b);
		p.dodajOdPrawej(k);
	}
	in.close();
	in.open("gracz1.txt", ios::in);				//wczytywanie danych dla pierwszego gracza
	if (!in.is_open()){
		cout << "Blad przy wczytywaniu gry!" << endl;
		system("PAUSE");
		return false;
	}
	string imie;
	int l_pkt;
	in >> imie;
	if (in.eof()){
		cout << "Blad przy wczytywaniu gry!" << endl;
		system("PAUSE");
		return false;
	}
	nr1.zmienImie(imie);
	in >> l_pkt;
	if (in.eof()){
		cout << "Blad przy wczytywaniu gry!" << endl;
		system("PAUSE");
		return false;
	}
	nr1.dodajDoPunktow(l_pkt);
	while (!in.eof()){
		in >> a;
		if (in.eof()){
			break;
		}
		in >> b;
		if (in.fail()){
			cout << "Blad przy wczytywaniu gry!" << endl;
			system("PAUSE");
			return false;
		}
		k.zmienPierwsza(a);
		k.zmienDruga(b);
		nr1.dodajKlocek(k);
	}
	in.close();
	in.open("gracz2.txt", ios::in);				//wczytywanie danych dla drugiego gracza
	if (!in.is_open()){
		cout << "Blad przy wczytywaniu gry!" << endl;
		system("PAUSE");
		return false;
	}
	in >> imie;
	if (in.eof()){
		cout << "Blad przy wczytywaniu gry!" << endl;
		system("PAUSE");
		return false;
	}
	nr2.zmienImie(imie);
	in >> l_pkt;
	if (in.eof()){
		cout << "Blad przy wczytywaniu gry!" << endl;
		system("PAUSE");
		return false;
	}
	nr2.dodajDoPunktow(l_pkt);
	in >> wybor;
	if (in.eof()){
		cout << "Blad przy wczytywaniu gry!" << endl;
		system("PAUSE");
		return false;
	}
	while (!in.eof()){
		in >> a;
		if (in.eof()){
			break;
		}
		in >> b;
		if (in.fail()){
			cout << "Blad przy wczytywaniu gry!" << endl;
			system("PAUSE");
			return false;
		}
		k.zmienPierwsza(a);
		k.zmienDruga(b);
		nr2.dodajKlocek(k);
	}
	in.close();
	in.open("daneGry.txt", ios::in);
	if (!in.is_open()){
		cout << "Blad przy wczytywaniu gry!" << endl;
		system("PAUSE");
		return false;
	}
	in >> kolejnosc;
	if (in.eof()){
		cout << "Blad przy wczytywaniu gry!" << endl;
		system("PAUSE");
		return false;
	}
	in >> limitPkt;
	in.close();
	return true;
}
