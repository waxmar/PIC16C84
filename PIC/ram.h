#ifndef RAM_H
#define RAM_H

#include "speicher.h"

class Ram : public Speicher
{
public:
    Ram();

    int lesen(int adresse, int bank);
    int lesen(int adresse);
    void schreiben(int wert, int adresse, int bank);
    void schreiben(int wert, int adresse);

    void setzeZBit();
    void loescheZBit();
    void setzeCBit();
    void loescheCBit();
    void setzeDCBit();
    void loescheDCBit();

    static const int STATUS = 0x03;

private:
    //Speicherbänke definieren S.6
     int bank1[0x50];
     int bank0[0x50];

     // Mapping der Speicherbänke
     int* adressen[2][0x50];




     // Abfrage der aktuellen Ba
     int getActiveBank();

};

#endif // RAM_H
