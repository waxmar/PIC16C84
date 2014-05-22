#include "alu.h"
#include "programmzaehler.h"
#include "steuerwerk.h"
#include "ram.h"
#include "stack.h"
#include "wregister.h"
#include "bitoperationen.h"

#include <iostream>

Alu::Alu(Steuerwerk* steuerwerk)
{
    this->steuerwerk = steuerwerk;
}

void Alu::zaehlerstandErhoehen()
{
    int zaehlerstand = steuerwerk->getProgrammzaehler()->lesen(Speicher::NOADDRESS);
    steuerwerk->getProgrammzaehler()->schreiben(zaehlerstand+1,Speicher::NOADDRESS);
}

void Alu::ausfuehrenADDWF(int befehl)
{
    zaehlerstandErhoehen();

    int f = steuerwerk->getRam()->lesen(befehl & 0x007f);
    int w = steuerwerk->getW()->lesen(Speicher::NOADDRESS);
    int ergebnis = f + w;

    if (pruefeCarry(ergebnis))
        steuerwerk->getRam()->setzeCBit();

    if (pruefeZero(ergebnis))
        steuerwerk->getRam()->setzeZBit();

    if (pruefeDigitCarry(f,w))
        steuerwerk->getRam()->setzeDCBit();

    if (Bitoperationen::pruefeBit(befehl,7) == STOREBACKINF)
        steuerwerk->getRam()->schreiben(ergebnis, befehl & 0x007f);
    else
        steuerwerk->getW()->schreiben(ergebnis, Speicher::NOADDRESS);
}

void Alu::ausfuehrenANDWF(int befehl)
{
    zaehlerstandErhoehen();

    int f = steuerwerk->getRam()->lesen(befehl & 0x007f);
    int w = steuerwerk->getW()->lesen(Speicher::NOADDRESS);
    int ergebnis = (f & w);

    if (pruefeZero(ergebnis))
        steuerwerk->getRam()->setzeZBit();

    if (Bitoperationen::pruefeBit(befehl,7) == STOREBACKINF)
        steuerwerk->getRam()->schreiben(ergebnis, befehl & 0x007f);
    else
        steuerwerk->getW()->schreiben(ergebnis, Speicher::NOADDRESS);
}

void Alu::ausfuehrenCLRF(int befehl)
{
    zaehlerstandErhoehen();

    int f = steuerwerk->getRam()->lesen(befehl & 0x007f);
    int b = ((befehl & 0x0380) >> 7);

    steuerwerk->getRam()->schreiben(Bitoperationen::loescheBit(f,b), befehl & 0x007f);

}

void Alu::ausfuehrenCLRW(int befehl)
{
    zaehlerstandErhoehen();

    steuerwerk->getW()->schreiben(0, Speicher::NOADDRESS);
    steuerwerk->getRam()->setzeZBit();
}

void Alu::ausfuehrenCOMF(int befehl)
{

}

void Alu::ausfuehrenDECF(int befehl)
{

}

void Alu::ausfuehrenDECFSZ(int befehl)
{

}

void Alu::ausfuehrenINCF(int befehl)
{

}

void Alu::ausfuehrenINCFSZ(int befehl)
{

}

void Alu::ausfuehrenIORWF(int befehl)
{

}

void Alu::ausfuehrenMOVF(int befehl)
{

}

void Alu::ausfuehrenMOVWF(int befehl)
{

}

void Alu::ausfuehrenNOP()
{
    zaehlerstandErhoehen();
}

void Alu::ausfuehrenRLF(int befehl)
{

}

void Alu::ausfuehrenRRF(int befehl)
{

}

void Alu::ausfuehrenSUBWF(int befehl)
{

}

void Alu::ausfuehrenSWAPF(int befehl)
{

}

void Alu::ausfuehrenXORWF(int befehl)
{

}

void Alu::ausfuehrenBCF(int befehl)
{

}

void Alu::ausfuehrenBSF(int befehl)
{

}

void Alu::ausfuehrenBTFSC(int befehl)
{

}

void Alu::ausfuehrenBTFSS(int befehl)
{

}

void Alu::ausfuehrenADDLW(int befehl)
{
    zaehlerstandErhoehen();

    int konstante = (befehl & 0x00ff);
    int w = steuerwerk->getW()->lesen(Speicher::NOADDRESS);
    int ergebnis = konstante + w;

    if (pruefeCarry(ergebnis))
        steuerwerk->getRam()->setzeCBit();

    if (pruefeZero(ergebnis))
        steuerwerk->getRam()->setzeZBit();

    if (pruefeDigitCarry(konstante,w))
        steuerwerk->getRam()->setzeDCBit();

    steuerwerk->getW()->schreiben(ergebnis,Speicher::NOADDRESS);
}

void Alu::ausfuehrenANDLW(int befehl)
{
    zaehlerstandErhoehen();

    int konstante = (befehl & 0x00ff);
    int w = steuerwerk->getW()->lesen(Speicher::NOADDRESS);
    int ergebnis = (konstante & w);

    if (pruefeZero(ergebnis))
        steuerwerk->getRam()->setzeZBit();

    steuerwerk->getW()->schreiben(ergebnis,Speicher::NOADDRESS);
}

void Alu::ausfuehrenCALL(int befehl)
{
    int ruecksprungAdresse = steuerwerk->getProgrammzaehler()->lesen(Speicher::NOADDRESS)+1;
    steuerwerk->getStack()->schreiben(ruecksprungAdresse,Speicher::NOADDRESS);

    int sprungadresse = sprungadresseBerechnen(befehl);
    steuerwerk->getProgrammzaehler()->schreiben(sprungadresse,Speicher::NOADDRESS);
}

void Alu::ausfuehrenCLRWDT(int befehl)
{

}

void Alu::ausfuehrenGOTO(int befehl)
{

    int sprungadresse = sprungadresseBerechnen(befehl);

    steuerwerk->getProgrammzaehler()->schreiben(sprungadresse,Speicher::NOADDRESS);
}

void Alu::ausfuehrenIORLW(int befehl)
{

}

void Alu::ausfuehrenMOVLW(int befehl)
{

}

void Alu::ausfuehrenRETFIE(int befehl)
{

}

void Alu::ausfuehrenRETLW(int befehl)
{

}

void Alu::ausfuehrenRETURN(int befehl)
{

}

void Alu::ausfuehrenSLEEP(int befehl)
{

}

void Alu::ausfuehrenSUBLW(int befehl)
{

}

void Alu::ausfuehrenXORLW(int befehl)
{

}

int Alu::sprungadresseBerechnen(int befehl)
{
    int konstante = (befehl & 0x7ff);
    int pclath = steuerwerk->getRam()->lesen(0x0A);
    pclath = (pclath & 0x18) << 8;
    int sprungadresse = (pclath | konstante);

    return sprungadresse;
}

bool Alu::pruefeCarry(int ergebnis)
{
    return (ergebnis >= 0x100);
}

bool Alu::pruefeZero(int ergebnis)
{
    return ((ergebnis & 0x00ff) == 0);
}

bool Alu::pruefeDigitCarry(int konstante, int w)
{
    int ergebnis = (konstante & 0x000f) + (w & 0x000f);
    return (ergebnis >= 0x10);
}
