#ifndef PROGRAMMZAEHLER_H
#define PROGRAMMZAEHLER_H

#include "speicher.h"
#include <QList>

class Codezeile;
class Programmspeicher;

class Programmzaehler : public Speicher
{
public:
    Programmzaehler();

    int lesen(int adresse);
    void schreiben(int wert, int adresse);

    void initialisieren(QList<Codezeile>::iterator initAdresse);
private:
    QList<Codezeile>::iterator startAdresse;
    QList<Codezeile>::iterator pc;
};

#endif // PROGRAMMZAEHLER_H
