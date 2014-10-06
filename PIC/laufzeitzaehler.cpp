#include "laufzeitzaehler.h"
#include "steuerwerk.h"
#include "interruptsteuerung.h"
#include "timersteuerung.h"
#include "watchdog.h"

LaufzeitZaehler::LaufzeitZaehler(Steuerwerk* steuerwerk)
{
    this->steuerwerk = steuerwerk;
    befehlszyklen = 0;
}

//Anzahl der Befehlszyklen wird um 1 bzw. 2 erh�ht
void LaufzeitZaehler::zyklenInkrementieren(int anzahlZyklen)
{
    if(anzahlZyklen != 1 && anzahlZyklen != 2) //pr�ft ob Erh�hung ein g�ltiger Wert ist
        return;

    for(int i=0; i < anzahlZyklen; i++)
    {
       befehlszyklen++;
       // Timer nach jedem Zyklus handlen
       steuerwerk->getTimerSteuerung()->handleTimer0();

       // Interrupts nach jedem Zyklus pr�fen
       steuerwerk->getInterruptSteuerung()->checkForInterrupt();

       steuerwerk->getWatchdog()->incrementWDT();
    }
}

double LaufzeitZaehler::getLaufzeit()
{
   return (double)befehlszyklen * 0.4; //Quarzfrequenz
}

int LaufzeitZaehler::getZyklen()
{
    return befehlszyklen;
}
