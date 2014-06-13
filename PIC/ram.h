#ifndef RAM_H
#define RAM_H

#include "speicher.h"

class Steuerwerk;

class Ram : public Speicher
{
public:
    Ram(Steuerwerk* steuerwerk);

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

    static const int TMR0 = 0x01;
    static const int OPTION = 0x01;
    static const int PCL = 0x02;
    static const int STATUS = 0x03;
    static const int FSR = 0x04;
    static const int PORTA = 0x05;
    static const int TRISA = 0x05;
    static const int PORTB = 0x06;
    static const int TRISB = 0x06;
    static const int EEDATA = 0x08;
    static const int EECON1 = 0x08;
    static const int EEADR = 0x09;
    static const int EECON2 = 0x09;
    static const int PCLATH = 0x0A;
    static const int INTCON = 0x0B;

private:
    //Speicherbänke definieren S.6
    int bank1[0x50];
    int bank0[0x50];

    // Mapping der Speicherbänke
    int* adressen[2][0x50];

    Steuerwerk* steuerwerk;


    // Abfrage der aktuellen Ba
    int getActiveBank();

};

#endif // RAM_H
