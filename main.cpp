#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <cstdio>
#include <windows.h>

using namespace std;

struct Uzytkownik {
    int id;
    string login, haslo;
};

struct Adresat {
    int id, idUzytkownika;
    string imie, nazwisko, adres, numerTelefonu, email;
};

string wczytajLinie() {
    string wejscie = "";
    getline(cin,wejscie);
    return wejscie;
}

char wczytajZnak() {
    string wejscie = "";
    char znak = {0};

    while(true) {
        getline(cin,wejscie);

        if(wejscie.length() == 1) {
            znak = wejscie[0];
            break;
        }
        cout << "To nie jest pojedynczy znak. Wpisz ponownie" << endl;
    }
    return znak;
}

int wczytajLiczbeCalkowita() {
    string wejscie = "";
    int liczba = 0;

    while(true) {
        getline(cin, wejscie);

        stringstream myStream(wejscie);
        if (myStream >> liczba)
            break;
        cout << "To nie jest liczba. Wpisz ponownie." << endl;
    }
    return liczba;
}

void zapiszDoPlikuTekstowegoUzytkownicy(Uzytkownik uzytkownik) {

    fstream plik;
    plik.open("uzytkownicy.txt", ios::app);

    plik<<uzytkownik.id<< '|' << uzytkownik.login << '|' << uzytkownik.haslo << '|'  << endl;
    plik.close();
}

void nadpiszPlikTekstowyUzytkownicy(vector <Uzytkownik> uzytkownicy) {
    fstream plik;
    plik.open("uzytkownicy.txt", ios::out);

    for (Uzytkownik uzytkownik : uzytkownicy) {
        plik << uzytkownik.id << '|' << uzytkownik.login << '|' << uzytkownik.haslo << '|' << endl;
    }
    plik.close();
}

void rejestracjaUzytkownika(vector <Uzytkownik> &uzytkownicy) {
    Uzytkownik uzytkownik;
    string login, haslo;
    cout << "Podaj login: ";
    login = wczytajLinie();
    cout << "Podaj haslo: ";
    haslo = wczytajLinie();

    uzytkownik.login = login;
    uzytkownik.haslo = haslo;
    uzytkownik.id = uzytkownicy.empty() ? 1 : uzytkownicy.back().id + 1;
    int id = uzytkownik.id;

    uzytkownicy.push_back(uzytkownik);
    zapiszDoPlikuTekstowegoUzytkownicy(uzytkownik);
    cout << endl;
    cout << "Uzytkownik zostal zarejestrowany" << endl;
    cout << endl;
    cout << "Press any key to continue ... ";
    getchar();
}

void wczytajZPlikuTekstowegoUzytkownicy(vector <Uzytkownik> &uzytkownicy) {
    ifstream plik("uzytkownicy.txt", ios::in);
    if (plik.is_open()) {
        string linia;
        while (getline(plik, linia)) {
            stringstream ss(linia);
            string pole;
            Uzytkownik uzytkownik;
            getline(ss, pole, '|');
            uzytkownik.id = stoi(pole);
            getline(ss, pole, '|');
            uzytkownik.login = pole;
            getline(ss, pole, '|');
            uzytkownik.haslo = pole;
            getline(ss, pole, '|');

            uzytkownicy.push_back(uzytkownik);
        }
        plik.close();
    }
}

void zmianaHaslaUzytkownika(vector <Uzytkownik> &uzytkownicy, string szukanyLogin, string szukaneHaslo) {
    string noweHaslo;
    cout <<endl;
    cout << "Podaj nowe haslo: ";
    noweHaslo = wczytajLinie();

    for(size_t i = 0; i < uzytkownicy.size(); i++) {
        if(uzytkownicy[i].login == szukanyLogin && uzytkownicy[i].haslo == szukaneHaslo) {
            uzytkownicy[i].haslo = noweHaslo;
            break;
        }
    }
    cout << "Haslo zostalo zmienione";
    cout << endl;
    cout << "Press any key to continue ... ";
    getchar();
    nadpiszPlikTekstowyUzytkownicy(uzytkownicy);
}

int numerIdUzytkownika(vector <Uzytkownik> &uzytkownicy,string szukanyLogin, string szukaneHaslo) {
    int idUzytkownika;

    for(size_t i = 0; i < uzytkownicy.size(); i++) {
        if(uzytkownicy[i].login == szukanyLogin && uzytkownicy[i].haslo == szukaneHaslo) {
            return uzytkownicy[i].id;
        }
    }
    return 0;
}

void wyswietlWszystkichAdresatowUzytkownika(vector<Adresat> adresaci, int idUzytkownika) {
    string imie, nazwisko, numerTelefonu, email, adres;
    int id;

    for(size_t i = 0; i < adresaci.size(); i++) {
        if(adresaci[i].idUzytkownika == idUzytkownika) {

        id = adresaci[i].id;
        imie = adresaci[i].imie;
        nazwisko = adresaci[i].nazwisko;
        numerTelefonu = adresaci[i].numerTelefonu;
        email = adresaci[i].email;
        adres = adresaci[i].adres;

        cout << endl;
        cout << "Id:" << '\t' << '\t' << '\t' << id << endl;
        cout << "Imie:"  << '\t' << '\t' << '\t' << imie << endl;
        cout << "Nazwisko:" << '\t' << '\t' << nazwisko <<endl;
        cout << "Numer telefonu:" << '\t' << '\t' << numerTelefonu << endl;
        cout << "Email:" << '\t' << '\t' << '\t' << email << endl;
        cout << "Adres:" << '\t' << '\t' << '\t' << adres << endl;
        }
    }

    cout <<endl;
    cout << "Press any key to continue . . . ";
    getchar();
}

void zapiszDoPlikuTekstowegoAdresaci(Adresat adresat, int idUzytkownika) {

    fstream plik;
    plik.open("ksiazka_adresowa.txt", ios::app);

    plik<<adresat.id<< '|' <<adresat.idUzytkownika<< '|' << adresat.imie << '|' << adresat.nazwisko << '|' << adresat.numerTelefonu << '|' << adresat.email << '|' << adresat.adres << '|' << endl;
    plik.close();
}

int znajdzOstatnieIdAdresata() {
    ifstream plik("ksiazka_adresowa.txt", ios::in);
    int ostatnieId = 0;
    if (plik.is_open()) {
        string linia;
        while (getline(plik, linia)) {
            stringstream ss(linia);
            string pole;
            int id;
            getline(ss, pole, '|');
            id = stoi(pole);
            if (id > ostatnieId) {
                ostatnieId = id;
            }
        }
        plik.close();
    }
    return ostatnieId;
}

void dodajAdresataDoKsiazki(vector <Adresat> &adresaci,vector <Uzytkownik> &uzytkownicy, int idUzytkownika, int &ostatnieId) {

    Adresat adresat;
    string imie, nazwisko, numerTelefonu, email, adres;
    cout << endl;
    cout << "Podaj imie: ";
    imie = wczytajLinie();
    cout << "Podaj nazwisko: ";
    nazwisko = wczytajLinie();
    cout << "Podaj numer telefonu: ";
    cin.sync();
    numerTelefonu = wczytajLinie();
    cout << "Podaj email: ";
    email = wczytajLinie();
    cout << "Podaj adres: ";
    adres = wczytajLinie();

    int id = adresat.id;
    adresat.imie = imie;
    adresat.nazwisko = nazwisko;
    adresat.numerTelefonu = numerTelefonu;
    adresat.email = email;
    adresat.adres = adres;
    adresat.id = ++ostatnieId;
    adresat.idUzytkownika = idUzytkownika;

    adresaci.push_back(adresat);
    zapiszDoPlikuTekstowegoAdresaci(adresat, idUzytkownika);
    cout << endl;
    cout << "Adresat zostal dodany" << endl;
    cout << endl;
    cout << "Press any key to continue ... ";
    getchar();
}

void wczytajZPlikuTekstowegoAdresatUzytkownika(vector<Adresat> &adresaci, int idUzytkownika) {
    adresaci.clear();

    ifstream plik("ksiazka_adresowa.txt", ios::in);
    if (plik.is_open()) {
        string linia;
        Adresat adresat;
        while (getline(plik, linia)) {
            stringstream ss(linia);
            string pole;
            getline(ss, pole, '|');
            adresat.id = stoi(pole);
            getline(ss, pole, '|');
            adresat.idUzytkownika = stoi(pole);
            getline(ss, pole, '|');
            adresat.imie = pole;
            getline(ss, pole, '|');
            adresat.nazwisko = pole;
            getline(ss, pole, '|');
            adresat.numerTelefonu = pole;
            getline(ss, pole, '|');
            adresat.email = pole;
            getline(ss, pole, '|');
            adresat.adres = pole;

            if(adresat.idUzytkownika == idUzytkownika) {
                adresaci.push_back(adresat);
            }
        }
        plik.close();
    }
}

void wczytajZPlikuTekstowegoAdresat(vector<Adresat> &adresaci) {
    adresaci.clear();

    ifstream plik("ksiazka_adresowa.txt", ios::in);
    if (plik.is_open()) {
        string linia;
        Adresat adresat;
        while (getline(plik, linia)) {
            stringstream ss(linia);
            string pole;
            getline(ss, pole, '|');
            adresat.id = stoi(pole);
            getline(ss, pole, '|');
            adresat.idUzytkownika = stoi(pole);
            getline(ss, pole, '|');
            adresat.imie = pole;
            getline(ss, pole, '|');
            adresat.nazwisko = pole;
            getline(ss, pole, '|');
            adresat.numerTelefonu = pole;
            getline(ss, pole, '|');
            adresat.email = pole;
            getline(ss, pole, '|');
            adresat.adres = pole;

            adresaci.push_back(adresat);

        }
        plik.close();
    }
}

void usunAdresata(vector<Adresat> &adresaci, int idUzytkownika) {
    char klawiszPotwierdzajacy;
    int idAdresataDoUsuniecia;
    cout << "Podaj id adresata: ";
    idAdresataDoUsuniecia = wczytajLiczbeCalkowita();
    cout << "Jesli napewno chcesz usunac adresata wcisnij klawisz: 't': ";
    klawiszPotwierdzajacy = wczytajZnak();

    if (klawiszPotwierdzajacy == 't') {
        wczytajZPlikuTekstowegoAdresat(adresaci);
        bool adresatZnaleziony = false;
        for (size_t i = 0; i < adresaci.size(); i++) {
            if (adresaci[i].id == idAdresataDoUsuniecia && adresaci[i].idUzytkownika == idUzytkownika) {
                adresaci.erase(adresaci.begin() + i);
                adresatZnaleziony = true;
                break;
            }
        }
        if (adresatZnaleziony) {
            fstream plik;
            plik.open("ksiazka_adresowa_tymczasowa.txt", ios::out);

            for (Adresat adresat : adresaci) {
                plik << adresat.id << '|' << adresat.idUzytkownika << '|'<< adresat.imie << '|'<< adresat.nazwisko << '|' << adresat.numerTelefonu << '|' << adresat.email << '|' << adresat.adres << '|' << endl;
            }
            plik.close();

            remove("ksiazka_adresowa.txt");
            rename("ksiazka_adresowa_tymczasowa.txt", "ksiazka_adresowa.txt");

            cout << "Adresat zostal usuniety." << endl;
        } else {
            cout << "Adresat o podanym ID nie istnieje lub nie nalezy do zalogowanego uzytkownika." << endl;
        }
    } else {
        cout << "Adresat nie zostal usuniety." << endl;
    }
    cout << endl;
    cout << "Nacisnij dowolny klawisz, aby kontynuowac...";
    getchar();
}

void logowanieUzytkownika(vector<Uzytkownik> &uzytkownicy, vector<Adresat> &adresaci) {
    string szukanyLogin, szukaneHaslo;
    char wybor;
    cout << "Podaj login: ";
    szukanyLogin = wczytajLinie();

    bool znalezionoLogin = false;
    for(size_t i = 0; i < uzytkownicy.size(); i++) {
        if(uzytkownicy[i].login == szukanyLogin) {
            znalezionoLogin = true;
            break;
        }
    }
    if (!znalezionoLogin) {
        cout << "Podano nieprawidlowy login" << endl;
        Sleep(1000);
        cout << endl;
        return;
        exit(1);
    }

    bool znaleziono = false;
    for(int i = 3; i > 0; i--) {
        cout << "Pozostalo" << ' '<< i << ' '<< "proby" <<endl ;
        cout << "Podaj haslo: " << endl;
        szukaneHaslo = wczytajLinie();
        int idUzytkownika = numerIdUzytkownika(uzytkownicy, szukanyLogin, szukaneHaslo);
        wczytajZPlikuTekstowegoAdresatUzytkownika(adresaci, idUzytkownika);
        int ostatnieId = znajdzOstatnieIdAdresata();
        for(size_t i = 0; i < uzytkownicy.size(); i++) {
            if(uzytkownicy[i].login == szukanyLogin && uzytkownicy[i].haslo == szukaneHaslo) {
                while (true) {
                    system("cls");
                    cout << ">>> MENU UZYTKOWNIKA <<<" << endl << endl;
                    cout << "1. Dodaj adresata" << endl;
                    cout << "2. Wyszukaj po imieniu" <<endl;
                    cout << "3. Wyszukaj po nazwisku" <<endl;
                    cout << "4. Wyswietl wszystkich adresatow" <<endl;
                    cout << "5. Usun adresata" << endl;
                    cout << "6. Edytuj adresata"<<endl;
                    cout << endl;
                    cout << "7. Zmien haslo" << endl;
                    cout << "8. Wyloguj sie"<<endl;
                    cout << "9. Zamknij program"<<endl;
                    cout << endl;
                    cout << "Twoj wybor: " <<endl;
                    wybor = wczytajZnak();

                    switch(wybor) {
                    case '1' :
                        dodajAdresataDoKsiazki(adresaci,uzytkownicy, idUzytkownika, ostatnieId);
                        break;
                    case '2' :
                        wyszukajPoImieniuAdresata(adresaci);
                        break;
                    case '3' :
                        wyszukajAdresataPoNazwisku(adresaci);
                        break;
                    case '4' :
                        wyswietlWszystkichAdresatowUzytkownika(adresaci, idUzytkownika);
                        break;
                    case '5' :
                        usunAdresata(adresaci, idUzytkownika);
                        break;
                    case '6' :
                        edytujAdresata(adresaci, idUzytkownika);
                        break;
                    case '7' :
                        zmianaHaslaUzytkownika(uzytkownicy,szukanyLogin,szukaneHaslo);
                        break;
                    case '8':
                        return;
                        break;
                    default:
                        exit(1);
                    case '9':
                        exit(0);
                    }
                }
                znaleziono = true;
                break;
            }
        }
    }
    if(!znaleziono) {
        cout << "Podano nieprawidlowe haslo." <<endl;
    }
    cout << endl;
    cout << "Press any key to continue ... ";
    getchar();
}

int main() {
    char wybor;

    vector <Uzytkownik> uzytkownicy;
    vector <Adresat> adresaci;

    wczytajZPlikuTekstowegoUzytkownicy(uzytkownicy);

    while (true) {
        system("cls");
        cout << ">>> MENU GLOWNE <<<" << endl << endl;
        cout << "1. Rejestracja" << endl;
        cout << "2. Logowanie"<<endl;
        cout << "3. Koniec programu" <<endl;
        cout << endl;
        cout << "Twoj wybor: " <<endl;
        wybor = wczytajZnak();

        switch(wybor) {
        case '1' :
            rejestracjaUzytkownika(uzytkownicy);
            break;
        case '2':
            logowanieUzytkownika(uzytkownicy,adresaci);
            break;
        case '3':
            exit(0);
        }
    }
    return 0;
}
