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

Codezeile* Programmspeicher::getCodezeileAt(int adresse)
{
    QList<Codezeile>::iterator codezeile = rom.begin() + adresse;
    return &(*codezeile);
}

// returns NULL, if there is no element with this linenumber
Codezeile* Programmspeicher::findCodezeileByLinenumber(int linenumber)
{
    QList<Codezeile>::iterator codezeile = rom.begin();
    while(codezeile != rom.end())
    {
        if((&(*codezeile))->getTextzeile() == linenumber)
            return &(*codezeile);

        codezeile++;
    }

    return NULL;
}

//Ermittlung der ersten Adresse im Speicher
QList<Codezeile>::iterator Programmspeicher::getErsteAdresse()
{
    return rom.begin();
}
