#include "laufzeitzaehler.h"
#include "steuerwerk.h"

LaufzeitZaehler::LaufzeitZaehler(Steuerwerk* steuerwerk)
{
    this->steuerwerk = steuerwerk;
    befehlszyklen = 0;
    frequenz = 40000.0;
}

void LaufzeitZaehler::zyklenInkrementieren(int anzahlZyklen)
{
    if(anzahlZyklen != 0 || anzahlZyklen != 1)
        return;

    for(int i=0; i < anzahlZyklen; i++)
    {
       befehlszyklen++;
       // Timer
    }
}
