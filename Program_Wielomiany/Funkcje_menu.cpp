#include "Wielomian.h"

static const int MAX = 100;
int aktualny_rozmiar = 0;
Wielomian baza_wielomianow[MAX];

void dodawanie();
void odejmowanie();
void mnozenie();
void obliczanie_wartosci_wielomianu();

void brak_miejsca();
void brak_wielomianow();

void wypisz_baze()
{
    if (aktualny_rozmiar == 0)
    {
        cout << "                    Baza wielomianow                    " << endl;
        cout << "    ------------------------------------------------    " << endl;
        cout << "                Brak wielomianow w bazie!               " << endl;
        przedzial();
        return;
    }
    cout << "                    Baza wielomianow                    " << endl;
    cout << "    ------------------------------------------------    " << endl;
    for (int i = 0; i < aktualny_rozmiar; i++)
    {
        cout << "    " << i + 1 << ". ";
        baza_wielomianow[i].wypisz();
        cout << endl;
    }
    przedzial();
}

void dodaj_wielomian()
{
    bool wyjatek = false;
    string _stopien;
    int stopien;
    string _wspolczynnik;
    double wspolczynnik;
    if (aktualny_rozmiar >= MAX)
    {
        brak_miejsca();
        return;
    }
    while (1)
    {
        system("clear");
        przedzial();
        cout << "              Wprowadz stopien wielomianu:              " << endl;
        przedzial();
        if (wyjatek)
        {
            cout << "           Wprowadzono nieprawidlowy argument!          " << endl;
            przedzial();
        }
        wyjatek = false;

        cout << " Stopien: ";
        cin >> _stopien;
        try
        {
            stopien = stoi(_stopien);
        }
        catch (invalid_argument e)
        {
            wyjatek = true;
            continue;
        }
        wyjatek = false;
        break;
    }

    double tablica_wspolczynnikow[stopien + 1];
    for (int i = stopien; i >= 0; i--)
    {
        while (1)
        {
            system("clear");
            przedzial();
            cout << "              Wprowadz wspolczynnik przy x^" << i << ":           " << endl;
            przedzial();
            if (wyjatek)
            {
                cout << "           Wprowadzono nieprawidlowy argument!          " << endl;
                przedzial();
            }
            wyjatek = false;

            cout << " Wspolczynnik: ";
            cin >> _wspolczynnik;
            try
            {
                wspolczynnik = stod(_wspolczynnik);
            }
            catch (invalid_argument e)
            {
                wyjatek = true;
                continue;
            }
            tablica_wspolczynnikow[i] = wspolczynnik;
            wyjatek = false;
            break;
        }
    }
    baza_wielomianow[aktualny_rozmiar] = Wielomian(stopien, tablica_wspolczynnikow);
    aktualny_rozmiar++;
    return;
}

void wczytaj_wielomiany()
{
    bool wyjatek = false;
    system("clear");
    przedzial();
    cout << "          Wprowadz nazwe pliku z rozszerzeniem:         " << endl;
    przedzial();
    cout << " Nazwa pliku: ";
    string nazwa;
    cin >> nazwa;
    ifstream plik(nazwa);
    if (!plik.is_open())
    {
        while (1)
        {
            system("clear");
            przedzial();
            cout << "              Nie udalo sie otworzyc pliku!             " << endl;
            przedzial();
            cout << "                          Menu                          " << endl;
            cout << "    ------------------------------------------------    " << endl;
            cout << "    0. Powrot." << endl;
            przedzial();
            if (wyjatek)
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
            switch (wybor)
            {
            case 0:
                return;
            default:
                wyjatek = true;
                continue;
            };
        }
    }
    else
    {
        double _liczba;
        int _stopien;
        double *_wspolczynniki;
        bool flaga = false;
        int i;
        while (plik >> _liczba && aktualny_rozmiar < MAX)
        {
            //cout << _liczba << endl;
            if (!flaga)
            {
                _stopien = _liczba;
                _wspolczynniki = new double[_stopien + 1];
                flaga = true;
                i = _stopien;
            }
            else
            {
                _wspolczynniki[i] = _liczba;
                i--;
                if (i < 0)
                {
                    flaga = false;
                    baza_wielomianow[aktualny_rozmiar] = Wielomian(_stopien, _wspolczynniki);
                    aktualny_rozmiar++;
                }
            }
        }
        plik.close();
        if (aktualny_rozmiar >= MAX)
        {
            brak_miejsca();
            return;
        }
    }
    return;
}

void usun_wielomian()
{
    if (aktualny_rozmiar <= 0)
        brak_wielomianow();
    else
    {
        bool wyjatek = false;
        string _numer_wielomianu;
        int numer_wielomianu;
        while (1)
        {
            system("clear");
            przedzial();
            wypisz_baze();
            cout << "   Wprowadz numer porzadkowy wielomianu do usuniecia:   " << endl;
            przedzial();
            cout << "          Wprowadz '0', jesli chcesz powrocic.          " << endl;
            przedzial();
            if (wyjatek)
            {
                cout << "           Wprowadzono nieprawidlowy argument!          " << endl;
                przedzial();
            }
            wyjatek = false;

            cout << " Nr: ";
            cin >> _numer_wielomianu;
            try
            {
                numer_wielomianu = stoi(_numer_wielomianu);
            }
            catch (invalid_argument e)
            {
                wyjatek = true;
                continue;
            }
            if (numer_wielomianu > aktualny_rozmiar)
            {
                wyjatek = true;
                continue;
            }
            wyjatek = false;
            break;
        }
        if (numer_wielomianu == 0)
            return;
        else
        {
            Wielomian nowa_baza_wielomianow[MAX];
            for (int i = 0; i < numer_wielomianu - 1; i++)
                nowa_baza_wielomianow[i] = Wielomian(baza_wielomianow[i].uzyskajStopien(), baza_wielomianow[i].uzyskajWspolczynniki());
            for (int i = numer_wielomianu; i < aktualny_rozmiar; i++)
                nowa_baza_wielomianow[i - 1] = Wielomian(baza_wielomianow[i].uzyskajStopien(), baza_wielomianow[i].uzyskajWspolczynniki());
            Wielomian nowy_wielomian;
            for (int i = 0; i < MAX; i++)
                baza_wielomianow[i] = nowy_wielomian;
            for (int i = 0; i < aktualny_rozmiar; i++)
                baza_wielomianow[i] = nowa_baza_wielomianow[i];
            aktualny_rozmiar--;
        }
    }
    return;
}

void wyczysc_baze()
{
    if (aktualny_rozmiar == 0)
        brak_wielomianow();
    else
    {
        Wielomian nowy_wielomian;
        for (int i = 0; i < MAX; i++)
            baza_wielomianow[i] = nowy_wielomian;
        aktualny_rozmiar = 0;
    }
    return;
}

void zapisz_do_pliku()
{
    bool wyjatek = false;
    system("clear");
    przedzial();
    cout << "          Wprowadz nazwe pliku z rozszerzeniem:         " << endl;
    przedzial();
    cout << " Nazwa pliku: ";
    string nazwa;
    cin >> nazwa;
    ofstream plik(nazwa);
    if (!plik.is_open())
    {
        while (1)
        {
            system("clear");
            przedzial();
            cout << "              Nie udalo sie otworzyc pliku!             " << endl;
            przedzial();
            cout << "                          Menu                          " << endl;
            cout << "    ------------------------------------------------    " << endl;
            cout << "    0. Powrot." << endl;
            przedzial();
            if (wyjatek)
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
            switch (wybor)
            {
            case 0:
                return;
            default:
                wyjatek = true;
                continue;
            };
        }
    }
    else
    {
        for (int i = 0; i < aktualny_rozmiar; i++)
        {
            int _stopien = baza_wielomianow[i].uzyskajStopien();
            plik << _stopien << " ";
            double *_wspolczynniki = baza_wielomianow[i].uzyskajWspolczynniki();
            for (int j = _stopien; j >= 0; j--)
            {
                plik << _wspolczynniki[j];
                if (j != 0)
                    plik << " ";
            }
            if (i != aktualny_rozmiar - 1)
                plik << endl;
        }
        plik.close();
    }
    return;
}

void dzialania()
{
    if (aktualny_rozmiar <= 0)
    {
        brak_wielomianow();
        return;
    }
    bool wyjatek = false;
    while (1)
    {
        system("clear");
        przedzial();
        wypisz_baze();
        cout << "                Dzialania na wielomianach               " << endl;
        cout << "    ------------------------------------------------    " << endl;
        cout << "    1. Dodawanie." << endl;
        cout << "    2. Odejmowanie." << endl;
        cout << "    3. Mnozenie." << endl;
        cout << "    4. Obliczanie wartosci wielomianu (a. Hornera)." << endl;
        cout << "    ------------------------------------------------    " << endl;
        cout << "    0. Powrot." << endl;
        przedzial();
        if (wyjatek)
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
        switch (wybor)
        {
        case 1:
            dodawanie();
            continue;
        case 2:
            odejmowanie();
            continue;
        case 3:
            mnozenie();
            continue;
        case 4:
            obliczanie_wartosci_wielomianu();
            continue;
        case 0:
            return;
        default:
            wyjatek = true;
            continue;
        };
    }
}

void dodawanie()
{
    bool wyjatek = false;
    int wybor1, wybor2;
    while (1)
    {
        system("clear");
        przedzial();
        wypisz_baze();
        cout << "        Wprowadz numery porzadkowe 2 wielomianow        " << endl;
        cout << "                   w celu ich dodania:                  " << endl;
        przedzial();
            cout << "          Wprowadz '0', jesli chcesz powrocic.          " << endl;
        przedzial();
        if (wyjatek)
        {
            cout << "           Wprowadzono nieprawidlowy argument!          " << endl;
            przedzial();
        }
        wyjatek = false;
        string _wybor1;
        cout << " Wielomian 1: ";
        cin >> _wybor1;
        string _wybor2;
        cout << " Wielomian 2: ";
        cin >> _wybor2;
        try
        {
            wybor1 = stoi(_wybor1);
            wybor2 = stoi(_wybor2);
        }
        catch (invalid_argument e)
        {
            wyjatek = true;
            continue;
        }
        if(wybor1 > aktualny_rozmiar || wybor2 > aktualny_rozmiar)
        {
            wyjatek = true;
            continue;
        }
        wyjatek = false;
        break;
    }
    if(wybor1 == 0 || wybor2 == 0)
        return;
    int stopien1 = baza_wielomianow[wybor1-1].uzyskajStopien();
    int stopien2 = baza_wielomianow[wybor2-1].uzyskajStopien();
    double *tablica_wspolczynnikow1 = baza_wielomianow[wybor1-1].uzyskajWspolczynniki();
    double *tablica_wspolczynnikow2 = baza_wielomianow[wybor2-1].uzyskajWspolczynniki();
    int stopien = max(stopien1, stopien2);
    double tablica_wspolczynnikow[stopien + 1];
    
    for (int i = stopien; i >= 0; i--)
    {
        if(i > stopien1)
        {
            tablica_wspolczynnikow[i] = tablica_wspolczynnikow2[i];
        }
        else if(i > stopien2)
        {
            tablica_wspolczynnikow[i] = tablica_wspolczynnikow1[i];
        }
        else 
        {
            tablica_wspolczynnikow[i] = tablica_wspolczynnikow2[i] + tablica_wspolczynnikow1[i];
        }
    }
    Wielomian nowy_wielomian = Wielomian(stopien, tablica_wspolczynnikow);
    //nowy_wielomian.wypisz();
    int wybor;
    while(1)
    {
        system("clear");
        przedzial();
        cout << "    ";
        baza_wielomianow[wybor1-1].wypisz();
        cout << endl;
        cout << "    +" << endl;
        cout << "    ";
        baza_wielomianow[wybor2-1].wypisz();
        cout << endl;
        cout << "    =" << endl;
        cout << "    ";
        nowy_wielomian.wypisz();
        cout << endl;
        przedzial();
        cout << "         Czy zapisac uzyskany wielomian do bazy?        " << endl;
        przedzial();
        cout << "                          Menu                          " << endl;
        cout << "    ------------------------------------------------    " << endl;
        cout << "    1. Zapisz wielomian." << endl;
        cout << "    ------------------------------------------------    " << endl;
        cout << "    0. Powrot." << endl;
        przedzial();
        cout << " Wybrane menu: ";
        wyjatek = false;
        string _wybor;
        cin >> _wybor;
        try
        {
            wybor = stoi(_wybor);
        }
        catch (invalid_argument e)
        {
            wyjatek = true;
            continue;
        }
        if(wybor > 1 || wybor < 0)
        {
            wyjatek = true;
            continue;
        }
        wyjatek = false;
        break;
    }
    if (wybor == 0)
        return;
    if (aktualny_rozmiar >= MAX)
    {
        brak_miejsca();
        return;
    }
    baza_wielomianow[aktualny_rozmiar] = nowy_wielomian;
    aktualny_rozmiar++;
    return;
}

void odejmowanie()
{
    bool wyjatek = false;
    int wybor1, wybor2;
    while (1)
    {
        system("clear");
        przedzial();
        wypisz_baze();
        cout << "        Wprowadz numery porzadkowe 2 wielomianow        " << endl;
        cout << "                   w celu ich odjecia:                  " << endl;
        przedzial();
            cout << "          Wprowadz '0', jesli chcesz powrocic.          " << endl;
        przedzial();
        if (wyjatek)
        {
            cout << "           Wprowadzono nieprawidlowy argument!          " << endl;
            przedzial();
        }
        wyjatek = false;
        string _wybor1;
        cout << " Wielomian 1: ";
        cin >> _wybor1;
        string _wybor2;
        cout << " Wielomian 2: ";
        cin >> _wybor2;
        try
        {
            wybor1 = stoi(_wybor1);
            wybor2 = stoi(_wybor2);
        }
        catch (invalid_argument e)
        {
            wyjatek = true;
            continue;
        }
        if(wybor1 > aktualny_rozmiar || wybor2 > aktualny_rozmiar)
        {
            wyjatek = true;
            continue;
        }
        wyjatek = false;
        break;
    }
    if(wybor1 == 0 || wybor2 == 0)
        return;
    int stopien1 = baza_wielomianow[wybor1-1].uzyskajStopien();
    int stopien2 = baza_wielomianow[wybor2-1].uzyskajStopien();
    double *tablica_wspolczynnikow1 = baza_wielomianow[wybor1-1].uzyskajWspolczynniki();
    double *tablica_wspolczynnikow2 = baza_wielomianow[wybor2-1].uzyskajWspolczynniki();
    int stopien = max(stopien1, stopien2);
    double tablica_wspolczynnikow[stopien + 1];
    
    for (int i = stopien; i >= 0; i--)
    {
        if(i > stopien1)
        {
            tablica_wspolczynnikow[i] = tablica_wspolczynnikow2[i]*(-1);
        }
        else if(i > stopien2)
        {
            tablica_wspolczynnikow[i] = tablica_wspolczynnikow1[i];
        }
        else 
        {
            tablica_wspolczynnikow[i] = tablica_wspolczynnikow1[i] - tablica_wspolczynnikow2[i];
        }
    }
    Wielomian nowy_wielomian = Wielomian(stopien, tablica_wspolczynnikow);
    //nowy_wielomian.wypisz();
    int wybor;
    while(1)
    {
        system("clear");
        przedzial();
        cout << "    ";
        baza_wielomianow[wybor1-1].wypisz();
        cout << endl;
        cout << "    -" << endl;
        cout << "    ";
        baza_wielomianow[wybor2-1].wypisz();
        cout << endl;
        cout << "    =" << endl;
        cout << "    ";
        nowy_wielomian.wypisz();
        cout << endl;
        przedzial();
        cout << "         Czy zapisac uzyskany wielomian do bazy?        " << endl;
        przedzial();
        cout << "                          Menu                          " << endl;
        cout << "    ------------------------------------------------    " << endl;
        cout << "    1. Zapisz wielomian." << endl;
        cout << "    ------------------------------------------------    " << endl;
        cout << "    0. Powrot." << endl;
        przedzial();
        cout << " Wybrane menu: ";
        wyjatek = false;
        string _wybor;
        cin >> _wybor;
        try
        {
            wybor = stoi(_wybor);
        }
        catch (invalid_argument e)
        {
            wyjatek = true;
            continue;
        }
        if(wybor > 1 || wybor < 0)
        {
            wyjatek = true;
            continue;
        }
        wyjatek = false;
        break;
    }
    if (wybor == 0)
        return;
    if (aktualny_rozmiar >= MAX)
    {
        brak_miejsca();
        return;
    }
    baza_wielomianow[aktualny_rozmiar] = nowy_wielomian;
    aktualny_rozmiar++;
    return;
}

void mnozenie()
{
    bool wyjatek = false;
    int wybor1, wybor2;
    while (1)
    {
        system("clear");
        przedzial();
        wypisz_baze();
        cout << "        Wprowadz numery porzadkowe 2 wielomianow        " << endl;
        cout << "                 w celu ich pomnozenia:                 " << endl;
        przedzial();
            cout << "          Wprowadz '0', jesli chcesz powrocic.          " << endl;
        przedzial();
        if (wyjatek)
        {
            cout << "           Wprowadzono nieprawidlowy argument!          " << endl;
            przedzial();
        }
        wyjatek = false;
        string _wybor1;
        cout << " Wielomian 1: ";
        cin >> _wybor1;
        string _wybor2;
        cout << " Wielomian 2: ";
        cin >> _wybor2;
        try
        {
            wybor1 = stoi(_wybor1);
            wybor2 = stoi(_wybor2);
        }
        catch (invalid_argument e)
        {
            wyjatek = true;
            continue;
        }
        if(wybor1 > aktualny_rozmiar || wybor2 > aktualny_rozmiar)
        {
            wyjatek = true;
            continue;
        }
        wyjatek = false;
        break;
    }
    if(wybor1 == 0 || wybor2 == 0)
        return;
    int stopien1 = baza_wielomianow[wybor1-1].uzyskajStopien();
    int stopien2 = baza_wielomianow[wybor2-1].uzyskajStopien();
    double *tablica_wspolczynnikow1 = baza_wielomianow[wybor1-1].uzyskajWspolczynniki();
    double *tablica_wspolczynnikow2 = baza_wielomianow[wybor2-1].uzyskajWspolczynniki();
    int stopien = stopien1 + stopien2;
    double tablica_wspolczynnikow[stopien + 1];
    
    for (int i = stopien1; i >= 0; i--)
    {
        for (int j = stopien2; j >= 0; j--)
        {
            tablica_wspolczynnikow[i+j] += tablica_wspolczynnikow1[i] * tablica_wspolczynnikow2[j];
        }
    }
    Wielomian nowy_wielomian = Wielomian(stopien, tablica_wspolczynnikow);
    //nowy_wielomian.wypisz();
    int wybor;
    while(1)
    {
        system("clear");
        przedzial();
        cout << "    ";
        baza_wielomianow[wybor1-1].wypisz();
        cout << endl;
        cout << "    *" << endl;
        cout << "    ";
        baza_wielomianow[wybor2-1].wypisz();
        cout << endl;
        cout << "    =" << endl;
        cout << "    ";
        nowy_wielomian.wypisz();
        cout << endl;
        przedzial();
        cout << "         Czy zapisac uzyskany wielomian do bazy?        " << endl;
        przedzial();
        cout << "                          Menu                          " << endl;
        cout << "    ------------------------------------------------    " << endl;
        cout << "    1. Zapisz wielomian." << endl;
        cout << "    ------------------------------------------------    " << endl;
        cout << "    0. Powrot." << endl;
        przedzial();
        cout << " Wybrane menu: ";
        wyjatek = false;
        string _wybor;
        cin >> _wybor;
        try
        {
            wybor = stoi(_wybor);
        }
        catch (invalid_argument e)
        {
            wyjatek = true;
            continue;
        }
        if(wybor > 1 || wybor < 0)
        {
            wyjatek = true;
            continue;
        }
        wyjatek = false;
        break;
    }
    if (wybor == 0)
        return;
    if (aktualny_rozmiar >= MAX)
    {
        brak_miejsca();
        return;
    }
    baza_wielomianow[aktualny_rozmiar] = nowy_wielomian;
    aktualny_rozmiar++;
    return;
}

void obliczanie_wartosci_wielomianu()
{
    bool wyjatek = false;
    int wybor1;
    double wybor2;
    while (1)
    {
        system("clear");
        przedzial();
        wypisz_baze();
        cout << "          Wprowadz numer porzadkowy wielomianu          " << endl;
        cout << "               i wartosc argumentu w celu               " << endl;
        cout << "            znalezienia wartosci wielomianu:            " << endl;
        przedzial();
            cout << "          Wprowadz '0', jesli chcesz powrocic.          " << endl;
        przedzial();
        if (wyjatek)
        {
            cout << "           Wprowadzono nieprawidlowy argument!          " << endl;
            przedzial();
        }
        wyjatek = false;
        string _wybor1;
        cout << " Nr: ";
        cin >> _wybor1;
        string _wybor2;
        cout << " Argument: ";
        cin >> _wybor2;
        try
        {
            wybor1 = stoi(_wybor1);
            wybor2 = stod(_wybor2);
        }
        catch (invalid_argument e)
        {
            wyjatek = true;
            continue;
        }
        if(wybor1 > aktualny_rozmiar)
        {
            wyjatek = true;
            continue;
        }
        wyjatek = false;
        break;
    }
    if(wybor1 == 0)
        return;
    int stopien = baza_wielomianow[wybor1-1].uzyskajStopien();
    double *tablica_wspolczynnikow = baza_wielomianow[wybor1-1].uzyskajWspolczynniki();
    
    double wynik = tablica_wspolczynnikow[stopien];
    for (int i = stopien-1; i >= 0; i--)
    {
        wynik = wynik*wybor2 + tablica_wspolczynnikow[i];
    }

    int wybor;
    while(1)
    {
        system("clear");
        przedzial();
        cout << "    W(x) = ";
        baza_wielomianow[wybor1-1].wypisz();
        cout << endl;
        cout << "    W(" << wybor2 << ") = " << wynik << endl;
        przedzial();
        cout << "                          Menu                          " << endl;
        cout << "    ------------------------------------------------    " << endl;
        cout << "    0. Powrot." << endl;
        przedzial();
        cout << " Wybrane menu: ";
        wyjatek = false;
        string _wybor;
        cin >> _wybor;
        try
        {
            wybor = stoi(_wybor);
        }
        catch (invalid_argument e)
        {
            wyjatek = true;
            continue;
        }
        if(wybor > 0 || wybor < 0)
        {
            wyjatek = true;
            continue;
        }
        wyjatek = false;
        break;
    }
    if (wybor == 0)
        return;
    return;
}

void brak_miejsca()
{
    bool wyjatek = false;
    while (1)
    {
        system("clear");
        przedzial();
        cout << "            Brak miejsca na nowe wielomiany!            " << endl;
        przedzial();
        cout << "                          Menu                          " << endl;
        cout << "    ------------------------------------------------    " << endl;
        cout << "    0. Powrot." << endl;
        przedzial();
        if (wyjatek)
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
        switch (wybor)
        {
        case 0:
            return;
        default:
            wyjatek = true;
            continue;
        };
    }
}

void brak_wielomianow()
{
    bool wyjatek = false;
    while (1)
    {
        system("clear");
        przedzial();
        cout << "                   Brak  wielomianow!                   " << endl;
        przedzial();
        cout << "                          Menu                          " << endl;
        cout << "    ------------------------------------------------    " << endl;
        cout << "    0. Powrot." << endl;
        przedzial();
        if (wyjatek)
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
        switch (wybor)
        {
        case 0:
            return;
        default:
            wyjatek = true;
            continue;
        };
    }
}

void przedzial()
{
    cout << "|======================================================|" << endl;
}