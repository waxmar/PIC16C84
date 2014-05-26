#include "programmspeicher.h"
#include "codezeile.h"


Programmspeicher::Programmspeicher()
{

}

//Auslesen der Speicherinhaltes an einer bestimmten Adresse
int Programmspeicher::lesen(int adresse)
{
    QList<Codezeile>::iterator befehlszeiger = rom.begin() + adresse;
    return befehlszeiger->getBefehl();
}

//Schreiben eines Wertes in den Speicher
void Programmspeicher::schreiben(int befehl, int textZeile)
{
    Codezeile* zeile = new Codezeile(befehl, textZeile);
    rom.append(*zeile);
}

//Ermittlung der ersten Adresse im Speicher
QList<Codezeile>::iterator Programmspeicher::getErsteAdresse()
{
    return rom.begin();
}
