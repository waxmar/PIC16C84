#ifndef LAUFZEITZAEHLER_H
#define LAUFZEITZAEHLER_H

class Steuerwerk;

class LaufzeitZaehler
{
public:
    LaufzeitZaehler(Steuerwerk* steuerwerk);

    double getLaufzeit();
    int getZyklen();

    void zyklenInkrementieren(int anzahlZyklen);
private:
    Steuerwerk* steuerwerk;
    int befehlszyklen;
};

#endif // LAUFZEITZAEHLER_H
