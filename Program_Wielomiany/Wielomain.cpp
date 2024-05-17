#include "Wielomian.h"

Wielomian::Wielomian()
{
    stopien = 0;
    wspolczynniki = new double[stopien+1];
    wspolczynniki[0] = 0;
}

Wielomian::Wielomian(int _stopien, double *_wspolczynniki)
{
    stopien = _stopien;
    wspolczynniki = new double[_stopien+1];
    for(int i = 0; i < _stopien+1; i++)
    {
        wspolczynniki[i] = _wspolczynniki[i];
    }
}

int Wielomian::uzyskajStopien()
{
    return stopien;
}

double* Wielomian::uzyskajWspolczynniki()
{
    return wspolczynniki;
}

void Wielomian::wypisz()
{
    double suma = 0;
    for (int i = stopien; i >= 0; i--)
    {
        if(wspolczynniki[i] < 0.0000000001 && wspolczynniki[i] > 0)
            wspolczynniki[i] = 0;
        suma += wspolczynniki[i];
        if (i == 0 && wspolczynniki[i] != 0 && suma-wspolczynniki[i] == 0)
            printf("%.2f ", wspolczynniki[i]);
        else if (i == 0 && wspolczynniki[i] != 0)
            printf("%+.2f ", wspolczynniki[i]);
        else if(stopien == 0 && wspolczynniki[i] == 0)
        {
            printf("%.2f ", wspolczynniki[i]);
        }
        else if(i == 0 && suma == 0 && wspolczynniki[i] == 0)
        {
            printf("%.2f ", wspolczynniki[i]);
        }
        else if (i == stopien || suma == 0)
        {
            if(wspolczynniki[i] != 0)
                printf("%.2f*x^%d ", wspolczynniki[i], i);
        }
        else if (suma - wspolczynniki[i] == 0)
        {
            if(wspolczynniki[i] != 0)
                printf("%.2f*x^%d ", wspolczynniki[i], i);
        }
        else
        {
            if(wspolczynniki[i] != 0)
                printf("%+.2f*x^%d ", wspolczynniki[i], i);
        }
    }
}