#include "alu.h"
#include "programmzaehler.h"
#include "steuerwerk.h"
#include "ram.h"
#include "stack.h"
#include "wregister.h"
#include "bitoperationen.h"
#include "laufzeitzaehler.h"

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

    steuerwerk->getLaufzeitZaehler()->zyklenInkrementieren(1);
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

    steuerwerk->getLaufzeitZaehler()->zyklenInkrementieren(1);
}

void Alu::ausfuehrenCLRF(int befehl)
{
    zaehlerstandErhoehen();

    int f = steuerwerk->getRam()->lesen(befehl & 0x007f);
    int b = ((befehl & 0x0380) >> 7);

    steuerwerk->getRam()->schreiben(Bitoperationen::loescheBit(f,b), befehl & 0x007f);

    steuerwerk->getLaufzeitZaehler()->zyklenInkrementieren(1);
}

void Alu::ausfuehrenCLRW(int befehl)
{
    zaehlerstandErhoehen();

    steuerwerk->getW()->schreiben(0, Speicher::NOADDRESS);
    steuerwerk->getRam()->setzeZBit();

    steuerwerk->getLaufzeitZaehler()->zyklenInkrementieren(1);
}

void Alu::ausfuehrenCOMF(int befehl)
{
    steuerwerk->getLaufzeitZaehler()->zyklenInkrementieren(1);
}

void Alu::ausfuehrenDECF(int befehl)
{
    steuerwerk->getLaufzeitZaehler()->zyklenInkrementieren(1);
}

void Alu::ausfuehrenDECFSZ(int befehl)
{
    steuerwerk->getLaufzeitZaehler()->zyklenInkrementieren(1);
}

void Alu::ausfuehrenINCF(int befehl)
{
    steuerwerk->getLaufzeitZaehler()->zyklenInkrementieren(1);
}

void Alu::ausfuehrenINCFSZ(int befehl)
{
    steuerwerk->getLaufzeitZaehler()->zyklenInkrementieren(1);
}

void Alu::ausfuehrenIORWF(int befehl)
{
    steuerwerk->getLaufzeitZaehler()->zyklenInkrementieren(1);
}

void Alu::ausfuehrenMOVF(int befehl)
{
    steuerwerk->getLaufzeitZaehler()->zyklenInkrementieren(1);
}

void Alu::ausfuehrenMOVWF(int befehl)
{
    steuerwerk->getLaufzeitZaehler()->zyklenInkrementieren(1);
}

void Alu::ausfuehrenNOP()
{
    zaehlerstandErhoehen();

    steuerwerk->getLaufzeitZaehler()->zyklenInkrementieren(1);
}

void Alu::ausfuehrenRLF(int befehl)
{
    zaehlerstandErhoehen();

    steuerwerk->getLaufzeitZaehler()->zyklenInkrementieren(1);
}

void Alu::ausfuehrenRRF(int befehl)
{
    zaehlerstandErhoehen();

    steuerwerk->getLaufzeitZaehler()->zyklenInkrementieren(1);
}

void Alu::ausfuehrenSUBWF(int befehl)
{
    zaehlerstandErhoehen();

    steuerwerk->getLaufzeitZaehler()->zyklenInkrementieren(1);
}

void Alu::ausfuehrenSWAPF(int befehl)
{
    zaehlerstandErhoehen();

    steuerwerk->getLaufzeitZaehler()->zyklenInkrementieren(1);
}

void Alu::ausfuehrenXORWF(int befehl)
{
    zaehlerstandErhoehen();

    steuerwerk->getLaufzeitZaehler()->zyklenInkrementieren(1);
}

void Alu::ausfuehrenBCF(int befehl)
{
    zaehlerstandErhoehen();

    steuerwerk->getLaufzeitZaehler()->zyklenInkrementieren(1);
}

void Alu::ausfuehrenBSF(int befehl)
{
    zaehlerstandErhoehen();

    steuerwerk->getLaufzeitZaehler()->zyklenInkrementieren(1);
}

void Alu::ausfuehrenBTFSC(int befehl)
{
    zaehlerstandErhoehen();

    steuerwerk->getLaufzeitZaehler()->zyklenInkrementieren(1);
}

void Alu::ausfuehrenBTFSS(int befehl)
{
    zaehlerstandErhoehen();

    steuerwerk->getLaufzeitZaehler()->zyklenInkrementieren(1);
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

    steuerwerk->getLaufzeitZaehler()->zyklenInkrementieren(1);
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

    steuerwerk->getLaufzeitZaehler()->zyklenInkrementieren(1);
}

void Alu::ausfuehrenCALL(int befehl)
{
    int ruecksprungAdresse = steuerwerk->getProgrammzaehler()->lesen(Speicher::NOADDRESS)+1;
    steuerwerk->getStack()->schreiben(ruecksprungAdresse,Speicher::NOADDRESS);

    int sprungadresse = sprungadresseBerechnen(befehl);
    steuerwerk->getProgrammzaehler()->schreiben(sprungadresse,Speicher::NOADDRESS);

    steuerwerk->getLaufzeitZaehler()->zyklenInkrementieren(2);
}

void Alu::ausfuehrenCLRWDT(int befehl)
{
    zaehlerstandErhoehen();

    steuerwerk->getLaufzeitZaehler()->zyklenInkrementieren(1);
}

void Alu::ausfuehrenGOTO(int befehl)
{

    int sprungadresse = sprungadresseBerechnen(befehl);

    steuerwerk->getProgrammzaehler()->schreiben(sprungadresse,Speicher::NOADDRESS);

    steuerwerk->getLaufzeitZaehler()->zyklenInkrementieren(2);
}

void Alu::ausfuehrenIORLW(int befehl)
{
    zaehlerstandErhoehen();

    steuerwerk->getLaufzeitZaehler()->zyklenInkrementieren(1);
}

void Alu::ausfuehrenMOVLW(int befehl)
{
    zaehlerstandErhoehen();

    steuerwerk->getLaufzeitZaehler()->zyklenInkrementieren(1);
}

void Alu::ausfuehrenRETFIE(int befehl)
{
    steuerwerk->getLaufzeitZaehler()->zyklenInkrementieren(2);
}

void Alu::ausfuehrenRETLW(int befehl)
{
    steuerwerk->getLaufzeitZaehler()->zyklenInkrementieren(2);
}

void Alu::ausfuehrenRETURN(int befehl)
{
    steuerwerk->getLaufzeitZaehler()->zyklenInkrementieren(2);
}

void Alu::ausfuehrenSLEEP(int befehl)
{
    steuerwerk->getLaufzeitZaehler()->zyklenInkrementieren(1);
}

void Alu::ausfuehrenSUBLW(int befehl)
{
    zaehlerstandErhoehen();

    steuerwerk->getLaufzeitZaehler()->zyklenInkrementieren(1);
}

void Alu::ausfuehrenXORLW(int befehl)
{
    zaehlerstandErhoehen();

    steuerwerk->getLaufzeitZaehler()->zyklenInkrementieren(1);
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
