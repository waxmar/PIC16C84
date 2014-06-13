#include "laufzeitzaehler.h"
#include "steuerwerk.h"
#include "interruptsteuerung.h"

LaufzeitZaehler::LaufzeitZaehler(Steuerwerk* steuerwerk)
{
    this->steuerwerk = steuerwerk;
    befehlszyklen = 0;
}

//Anzahl der Befehlszyklen wird um 1 bzw. 2 erhöht
void LaufzeitZaehler::zyklenInkrementieren(int anzahlZyklen)
{
    if(anzahlZyklen != 1 && anzahlZyklen != 2)
        return;

    for(int i=0; i < anzahlZyklen; i++)
    {
       befehlszyklen++;
       // Timer nach jedem Zyklus handlen

       // Interrupts nach jedem Zyklus prüfen
       steuerwerk->getInterruptSteuerung()->checkForInterrupt();
    }
}

double LaufzeitZaehler::getLaufzeit()
{
   return (double)befehlszyklen * 0.4d;
}
