#include "interruptsteuerung.h"

#include "steuerwerk.h"
#include "ram.h"
#include "bitoperationen.h"
#include "alu.h"

InterruptSteuerung::InterruptSteuerung(Steuerwerk* steuerwerk)
{
    this->steuerwerk = steuerwerk;

    // erleichtert den Zugriff auf das Intcon-Register
    intcon_register = steuerwerk->getRam()->getReferenceOf(Ram::INTCON, 0);
}

void InterruptSteuerung::checkForInterrupt()
{
    if(Bitoperationen::pruefeBit(*intcon_register, GIE))
    {
        if(Bitoperationen::pruefeBit(*intcon_register, T0IE) && Bitoperationen::pruefeBit(*intcon_register, T0IF))
            interruptAusloesen();

        if(Bitoperationen::pruefeBit(*intcon_register, INTE) && Bitoperationen::pruefeBit(*intcon_register, INTF))
            interruptAusloesen();

        if(Bitoperationen::pruefeBit(*intcon_register, RBIE) && Bitoperationen::pruefeBit(*intcon_register, RBIF))
            interruptAusloesen();
    }
}

void InterruptSteuerung::interruptAusloesen()
{
    // GIE-bit löschen
    *intcon_register = Bitoperationen::loescheBit(*intcon_register, GIE);

    steuerwerk->getAlu()->ausfuehrenCALL(INTERRUPT_ADDRESS);
}
