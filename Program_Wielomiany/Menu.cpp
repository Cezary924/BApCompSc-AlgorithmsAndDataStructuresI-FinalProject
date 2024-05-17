#include "Wielomian.h"

int main()
{
    bool wyjatek = false;
    while(1)
    {
        system("clear");
        przedzial();
        cout << "    Program implementujacy dzialania na wielomianach    " << endl;
        cout << "                      Projekt AISD1                     " << endl;
        cout << "    ------------------------------------------------    " << endl;
        cout << "                        Cezary924                       " << endl;
        przedzial();
        wypisz_baze();
        cout << "                          Menu                          " << endl;
        cout << "    ------------------------------------------------    " << endl;
        cout << "    1. Dzialania na wielomianach." << endl;
        cout << "    ------------------------------------------------    " << endl;
        cout << "    2. Dodaj wielomian do bazy." << endl;
        cout << "    3. Wczytaj baze wielomianow z pliku." << endl;
        cout << "    4. Usun wielomian z bazy." << endl;
        cout << "    5. Wyczysc baze wielomianow." << endl;
        cout << "    6. Zapisz baze wielomianow do pliku." << endl;
        cout << "    ------------------------------------------------    " << endl;
        cout << "    0. Wyjscie." << endl;
        przedzial();
        if(wyjatek)
        {
            cout << "           Wprowadzono nieprawidlowy argument!          " << endl;
            przedzial();
        }
        wyjatek = false;
        string _wybor;
        cout << " Wybrane menu: ";
        cin >> _wybor;
        int wybor;
        try
        {
            wybor = stoi(_wybor);
        }
        catch (invalid_argument e)
        {
            wyjatek = true;
            continue;
        }
        wyjatek = false;
        switch(wybor)
        {
            case 2:
                dodaj_wielomian();
                continue;
            case 3:
                wczytaj_wielomiany();
                continue;
            case 4:
                usun_wielomian();
                continue;
            case 5:
                wyczysc_baze();
                continue;
            case 6:
                zapisz_do_pliku();
                continue;
            case 1:
                dzialania();
                continue;
            case 0:
                przedzial();
                return 0;
            default:
                wyjatek = true;
                continue;
        };
    }
}