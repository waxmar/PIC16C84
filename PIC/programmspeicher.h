#ifndef PROGRAMMSPEICHER_H
#define PROGRAMMSPEICHER_H

#include "speicher.h"
#include <QList>

class Codezeile;

class Programmspeicher : public Speicher
{
public:
    Programmspeicher();

    int lesen(int adresse);
    void schreiben(int befehl, int textZeile);
    QList<Codezeile>::iterator getErsteAdresse();
    Codezeile* getCodezeileAt(int adresse);
    Codezeile* findCodezeileByLinenumber(int linenumber);
private:
    QList<Codezeile> rom;
};

#endif // PROGRAMMSPEICHER_H
