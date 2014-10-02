#include "timersteuerung.h"

#include <math.h>

#include "steuerwerk.h"
#include "ram.h"
#include "laufzeitzaehler.h"
#include "bitoperationen.h"
#include "interruptsteuerung.h"

TimerSteuerung::TimerSteuerung(Steuerwerk* steuerwerk)
{
    this->steuerwerk = steuerwerk;

    // erlaubt leichteren Zugriff auf TMR0- und OPTION-Register
    option_register = steuerwerk->getRam()->getReferenceOf(Ram::OPTION, 1);
    tmr0_register = steuerwerk->getRam()->getReferenceOf(Ram::TMR0, 0);
    ra_register = steuerwerk->getRam()->getReferenceOf(Ram::PORTA, 0);

    anzahlGueltigerFlanken = 0;
}

void TimerSteuerung::handleTimer0()
{
    bool timerInkrement;

    psaTeiler = calculatePsaTeiler();

    bool aktuellerWertRa4 = Bitoperationen::pruefeBit(*option_register, 4);

    if(Bitoperationen::pruefeBit(*option_register, T0CS))
        timerInkrement = externerTakt(aktuellerWertRa4);

    if(!Bitoperationen::pruefeBit(*option_register, T0CS))
        timerInkrement = internerTakt();

    if(timerInkrement)
        timerInkrementieren();

    alterWertRA4 = aktuellerWertRa4;
}

int TimerSteuerung::calculatePsaTeiler()
{
    int exponent = (*option_register & 0x07);
    return (int) pow(2.0, (double)(exponent + 1));
}

bool TimerSteuerung::externerTakt(int aktuellerWert)
{
    bool isTimerIncrement;

    if(Bitoperationen::pruefeBit(*option_register, T0SE))   // fallende Flanke
    {
        anzahlGueltigerFlanken++;
        if((anzahlGueltigerFlanken % psaTeiler == 0 || Bitoperationen::pruefeBit(*option_register, PSA)))
            isTimerIncrement = istFallendeFlanke(aktuellerWert);
    }
    else                                                    // steigende Flanke
    {
        anzahlGueltigerFlanken++;
        if((anzahlGueltigerFlanken % psaTeiler == 0 || Bitoperationen::pruefeBit(*option_register, PSA)))
            isTimerIncrement = istSteigendeFlanke(aktuellerWert);
    }

    return isTimerIncrement;
}

bool TimerSteuerung::internerTakt()
{
    if(Bitoperationen::pruefeBit(*option_register, PSA))
    {
        int zyklen = steuerwerk->getLaufzeitZaehler()->getZyklen();

        if(zyklen % psaTeiler == 0)
            return true;

        return false;
    }

    return true;
}

bool TimerSteuerung::istFallendeFlanke(int aktuellerWert)
{
    if(alterWertRA4 && !aktuellerWert)
        return true;

    return false;
}

bool TimerSteuerung::istSteigendeFlanke(int aktuellerWert)
{
    if(!alterWertRA4 && aktuellerWert)
        return true;

    return false;
}

void TimerSteuerung::timerInkrementieren()
{
    *tmr0_register++;
    if(*tmr0_register > 0xff)   // Überlauf
        steuerwerk->getInterruptSteuerung()->timerInterrupt();

    *tmr0_register = (*tmr0_register & 0xff);
}
