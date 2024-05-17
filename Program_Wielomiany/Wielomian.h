//#ifndef WIELOMIAN_H
//#define WIELOMIAN_H

#include <iostream>
#include <fstream>
#include <bits/stdc++.h>
#include <algorithm>
using namespace std;

class Wielomian
{
    private:
        int stopien;
        double *wspolczynniki;

    public:
        Wielomian();
        Wielomian(int, double*);
        int uzyskajStopien();
        double* uzyskajWspolczynniki();
        void wypisz();
};

void wypisz_baze();
void dodaj_wielomian();
void wczytaj_wielomiany();
void usun_wielomian();
void wyczysc_baze();
void zapisz_do_pliku();
void dzialania();
void przedzial();

//#endif