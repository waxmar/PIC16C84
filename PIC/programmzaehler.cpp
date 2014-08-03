#include "programmzaehler.h"
#include "codezeile.h"

Programmzaehler::Programmzaehler()
{
}

//Auslesen des aktuellen Programmzählers
int Programmzaehler::lesen(int adresse)
{    
    return pc - startAdresse;
}

//Erhöhen des ProgrammzÃ¤hlers um einen bestimmten Wert
void Programmzaehler::schreiben(int wert, int adresse)
{
    pc = startAdresse + wert;

    return;
}

//Initialisierung der Startadresse sowie des Programmzählers
void Programmzaehler::initialisieren(QList<Codezeile>::iterator initAdresse)
{
    startAdresse = initAdresse;
    pc = initAdresse;
}
