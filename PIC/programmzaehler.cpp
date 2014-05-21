#include "programmzaehler.h"
#include "codezeile.h"

Programmzaehler::Programmzaehler()
{
}

int Programmzaehler::lesen(int adresse)
{    
    return pc - startAdresse;
}

void Programmzaehler::schreiben(int wert, int adresse)
{
    pc = startAdresse + wert;

    return;
}

void Programmzaehler::initialisieren(QList<Codezeile>::iterator initAdresse)
{
    startAdresse = initAdresse;
    pc = initAdresse;
}
