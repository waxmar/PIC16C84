#include "programmzaehler.h"
#include "codezeile.h"

Programmzaehler::Programmzaehler()
{
}

//Auslesen des aktuellen Programmz�hlers
int Programmzaehler::lesen(int adresse)
{    
    return pc - startAdresse;
}

//Erh�hen des Programmzählers um einen bestimmten Wert
void Programmzaehler::schreiben(int wert, int adresse)
{
    pc = startAdresse + wert;

    return;
}

//Initialisierung der Startadresse sowie des Programmz�hlers
void Programmzaehler::initialisieren(QList<Codezeile>::iterator initAdresse)
{
    startAdresse = initAdresse;
    pc = initAdresse;
}
