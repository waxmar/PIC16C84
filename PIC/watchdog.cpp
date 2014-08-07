#include "watchdog.h"
#include "steuerwerk.h"
#include "laufzeitzaehler.h"
#include "ram.h"

#include <math.h>

Watchdog::Watchdog(Steuerwerk* steuerwerk)
{
    this->steuerwerk = steuerwerk;

    option_register = steuerwerk->getRam()->getReferenceOf(Ram::OPTION, 1);

    timerValue = 0;
}

void Watchdog::incrementWDT()
{
    psaTeiler = calculatePsaTeiler();

    int zyklen = steuerwerk->getLaufzeitZaehler()->getZyklen();

    if(zyklen % psaTeiler == 0)
        timerValue++;
}

void Watchdog::resetWDT() {
    timerValue = 0;
}

int Watchdog::calculatePsaTeiler()
{
    int exponent = (*option_register & 0x07);
    return (int) pow(2.0d, (double)(exponent));
}


