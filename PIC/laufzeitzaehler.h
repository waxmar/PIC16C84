#ifndef LAUFZEITZAEHLER_H
#define LAUFZEITZAEHLER_H

class Steuerwerk;

class LaufzeitZaehler
{
public:
    LaufzeitZaehler(Steuerwerk* steuerwerk);

    double getLaufzeit();

    void zyklenInkrementieren(int anzahlZyklen);
private:
    Steuerwerk* steuerwerk;
    int befehlszyklen;
    double frequenz;
};

#endif // LAUFZEITZAEHLER_H
