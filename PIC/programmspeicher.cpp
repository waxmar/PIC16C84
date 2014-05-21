#include "programmspeicher.h"
#include "codezeile.h"


Programmspeicher::Programmspeicher()
{

}

int Programmspeicher::lesen(int adresse)
{
    QList<Codezeile>::iterator befehlszeiger = rom.begin() + adresse;
    return befehlszeiger->getBefehl();
}

void Programmspeicher::schreiben(int befehl, int textZeile)
{
    Codezeile* zeile = new Codezeile(befehl, textZeile);
    rom.append(*zeile);
}

QList<Codezeile>::iterator Programmspeicher::getErsteAdresse()
{
    return rom.begin();
}
