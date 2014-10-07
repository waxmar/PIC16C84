#include "alu.h"
#include "programmzaehler.h"
#include "steuerwerk.h"
#include "ram.h"
#include "stack.h"
#include "wregister.h"
#include "bitoperationen.h"
#include "laufzeitzaehler.h"
#include "interruptsteuerung.h"

#include <iostream>

Alu::Alu(Steuerwerk* steuerwerk)
{
    this->steuerwerk = steuerwerk;
}

//Implementierung der PIC-Befehle//

void Alu::zaehlerstandErhoehen()
{
    int zaehlerstand = steuerwerk->getProgrammzaehler()->lesen(Speicher::NOADDRESS);
    steuerwerk->getProgrammzaehler()->schreiben(zaehlerstand+1,Speicher::NOADDRESS);
}

// addiert ausgewähltes Register mit W-Register und speichert Ergebnis an gewähltem Ort
void Alu::ausfuehrenADDWF(int befehl)
{
    zaehlerstandErhoehen();

    int f = steuerwerk->getRam()->lesen(befehl & 0x007f);
    int w = steuerwerk->getW()->lesen(Speicher::NOADDRESS);
    int ergebnis = f + w;

    if (pruefeCarry(ergebnis))
        steuerwerk->getRam()->setzeCBit();
    else
        steuerwerk->getRam()->loescheCBit();

    if (pruefeZero(ergebnis))
        steuerwerk->getRam()->setzeZBit();
    else
        steuerwerk->getRam()->loescheZBit();

    if (pruefeDigitCarry(f,w))
        steuerwerk->getRam()->setzeDCBit();
    else
        steuerwerk->getRam()->loescheDCBit();

    if (Bitoperationen::pruefeBit(befehl,7) == ZURUECKLADENINF) // prüft wo das Ergebnis gespeichert werden soll
        steuerwerk->getRam()->schreiben(ergebnis, (befehl & 0x007f));
    else
        steuerwerk->getW()->schreiben(ergebnis, Speicher::NOADDRESS);

    steuerwerk->getLaufzeitZaehler()->zyklenInkrementieren(1);
}

// Bitweise Verundung von gewähltem Register und W-Register, Speicherung an gewähltem Ort
void Alu::ausfuehrenANDWF(int befehl)
{
    zaehlerstandErhoehen();

    int f = steuerwerk->getRam()->lesen(befehl & 0x007f);
    int w = steuerwerk->getW()->lesen(Speicher::NOADDRESS);
    int ergebnis = (f & w);

    if (pruefeZero(ergebnis))
        steuerwerk->getRam()->setzeZBit();
    else
        steuerwerk->getRam()->loescheZBit();

    if (Bitoperationen::pruefeBit(befehl,7) == ZURUECKLADENINF) // prüft wo das Ergebnis gespeichert werden soll
        steuerwerk->getRam()->schreiben(ergebnis,(befehl & 0x007f));
    else
        steuerwerk->getW()->schreiben(ergebnis, Speicher::NOADDRESS);

    steuerwerk->getLaufzeitZaehler()->zyklenInkrementieren(1);
}

// löscht ein gewähltes Register
void Alu::ausfuehrenCLRF(int befehl)
{
    zaehlerstandErhoehen();

    steuerwerk->getRam()->schreiben(0, (befehl & 0x007f));

    steuerwerk->getLaufzeitZaehler()->zyklenInkrementieren(1);
}

// löscht das W-Register
void Alu::ausfuehrenCLRW(int befehl)
{
    zaehlerstandErhoehen();

    steuerwerk->getW()->schreiben(0, Speicher::NOADDRESS);
    steuerwerk->getRam()->setzeZBit();

    steuerwerk->getLaufzeitZaehler()->zyklenInkrementieren(1);
}

// bildet das Komplement eines Registers und speichert es an einem gewählten Ort
void Alu::ausfuehrenCOMF(int befehl)
{
    zaehlerstandErhoehen();

    int f = steuerwerk->getRam()->lesen(befehl & 0x007f);
    int ergebnis = (f ^ 0x00ff);

    if (pruefeZero(ergebnis))
        steuerwerk->getRam()->setzeZBit();
    else
        steuerwerk->getRam()->loescheZBit();

    if (Bitoperationen::pruefeBit(befehl,7) == ZURUECKLADENINF) // prüft wo das Ergebnis gespeichert werden soll
        steuerwerk->getRam()->schreiben(ergebnis, (befehl & 0x007f));

    else
        steuerwerk->getW()->schreiben(ergebnis, Speicher::NOADDRESS);

    steuerwerk->getLaufzeitZaehler()->zyklenInkrementieren(1);
}

// erniedrigt ein ausgewähltes Registers um 1
void Alu::ausfuehrenDECF(int befehl)
{
    zaehlerstandErhoehen();

    int f = steuerwerk->getRam()->lesen(befehl & 0x007f);
    int ergebnis = f-1;

    if (pruefeZero(ergebnis))
        steuerwerk->getRam()->setzeZBit();
    else
        steuerwerk->getRam()->loescheZBit();

    if (Bitoperationen::pruefeBit(befehl,7) == ZURUECKLADENINF) // prüft wo das Ergebnis gespeichert werden soll
        steuerwerk->getRam()->schreiben(ergebnis, (befehl & 0x007f));

    else
        steuerwerk->getW()->schreiben(ergebnis, Speicher::NOADDRESS);

    steuerwerk->getLaufzeitZaehler()->zyklenInkrementieren(1);
}

// erniedrigt ein ausgewähltes Registers um 1, falls das Ergebnis 0 ist wird des nächste Befehl übersprungen
void Alu::ausfuehrenDECFSZ(int befehl)
{
    zaehlerstandErhoehen();

    int f = steuerwerk->getRam()->lesen(befehl & 0x007f);
    int ergebnis = f-1;

    if (pruefeZero(ergebnis))
        steuerwerk->getRam()->setzeZBit();
    else
        steuerwerk->getRam()->loescheZBit();

    if (Bitoperationen::pruefeBit(befehl,7) == ZURUECKLADENINF) // prüft wo das Ergebnis gespeichert werden soll
        steuerwerk->getRam()->schreiben(ergebnis, (befehl & 0x007f));

    else
        steuerwerk->getW()->schreiben(ergebnis, Speicher::NOADDRESS);

    if (ergebnis == 0)
    {
        zaehlerstandErhoehen();
        steuerwerk->getLaufzeitZaehler()->zyklenInkrementieren(1);
    }

    else
        steuerwerk->getLaufzeitZaehler()->zyklenInkrementieren(2);
}

// erhöht ein ausgewähltes Register um 1
void Alu::ausfuehrenINCF(int befehl)
{
    zaehlerstandErhoehen();

    int f = steuerwerk->getRam()->lesen(befehl & 0x007f);
    int ergebnis = f+1;

    if (pruefeZero(ergebnis))
        steuerwerk->getRam()->setzeZBit();
    else
        steuerwerk->getRam()->loescheZBit();

    if (Bitoperationen::pruefeBit(befehl,7) == ZURUECKLADENINF) // prüft wo das Ergebnis gespeichert werden soll
        steuerwerk->getRam()->schreiben(ergebnis, (befehl & 0x007f));

    else
        steuerwerk->getW()->schreiben(ergebnis, Speicher::NOADDRESS);

    steuerwerk->getLaufzeitZaehler()->zyklenInkrementieren(1);
}

// erhöht ein ausgewähltes Register um 1, falls das Zero-Bit gesetzt wird, wird der nächste Befehl übersprungen
void Alu::ausfuehrenINCFSZ(int befehl)
{
    zaehlerstandErhoehen();

    int f = steuerwerk->getRam()->lesen(befehl & 0x007f);
    int ergebnis = f+1;

    if (pruefeZero(ergebnis))
        steuerwerk->getRam()->setzeZBit();
    else
        steuerwerk->getRam()->loescheZBit();

    if (Bitoperationen::pruefeBit(befehl,7) == ZURUECKLADENINF) // prüft wo das Ergebnis gespeichert werden soll
        steuerwerk->getRam()->schreiben(ergebnis, (befehl & 0x007f));

    else
        steuerwerk->getW()->schreiben(ergebnis, Speicher::NOADDRESS);

    if ((ergebnis & 0x00ff) == 0)
    {
        zaehlerstandErhoehen();
        steuerwerk->getLaufzeitZaehler()->zyklenInkrementieren(1);
    }

    else
        steuerwerk->getLaufzeitZaehler()->zyklenInkrementieren(2);
}

// Bitweises entweder-oder ein gewählten Registers und des W-Registers
void Alu::ausfuehrenIORWF(int befehl)
{
    zaehlerstandErhoehen();

    int f = steuerwerk->getRam()->lesen(befehl & 0x007f);
    int w = steuerwerk->getW()->lesen(Speicher::NOADDRESS);
    int ergebnis = (f | w);

    if (pruefeZero(ergebnis))
        steuerwerk->getRam()->setzeZBit();
    else
        steuerwerk->getRam()->loescheZBit();

    if (Bitoperationen::pruefeBit(befehl,7) == ZURUECKLADENINF) // prüft wo das Ergebnis gespeichert werden soll
        steuerwerk->getRam()->schreiben(ergebnis,(befehl & 0x007f));

    else
        steuerwerk->getW()->schreiben(ergebnis, Speicher::NOADDRESS);

    steuerwerk->getLaufzeitZaehler()->zyklenInkrementieren(1);
}

// Kopiert den Inhalt ein Registers in ein anderes Register
void Alu::ausfuehrenMOVF(int befehl)
{
    zaehlerstandErhoehen();

    int f = steuerwerk->getRam()->lesen(befehl & 0x007f);

    if (pruefeZero(f))
        steuerwerk->getRam()->setzeZBit();
    else
        steuerwerk->getRam()->loescheZBit();

    if (Bitoperationen::pruefeBit(befehl,7) == ZURUECKLADENINF) // prüft wo das Ergebnis gespeichert werden soll
        steuerwerk->getRam()->schreiben(f, (befehl & 0x007f));

    else
        steuerwerk->getW()->schreiben(f, Speicher::NOADDRESS);

    steuerwerk->getLaufzeitZaehler()->zyklenInkrementieren(1);
}

// schreibt den Inhalt eines gewählten Registers in das W-Register
void Alu::ausfuehrenMOVWF(int befehl)
{
    zaehlerstandErhoehen();

    int w = steuerwerk->getW()->lesen(Speicher::NOADDRESS);

    steuerwerk->getRam()->schreiben(w,(befehl & 0x007f));

    steuerwerk->getLaufzeitZaehler()->zyklenInkrementieren(1);
}

// führt keinen Befehl aus, nur Programmzähler wird erhöht
void Alu::ausfuehrenNOP()
{
    zaehlerstandErhoehen();

    steuerwerk->getLaufzeitZaehler()->zyklenInkrementieren(1);
}

// schiebt alle Bits eines gewählten Registers nach links, Carry-Bit wird eingeschoben
void Alu::ausfuehrenRLF(int befehl)
{
    zaehlerstandErhoehen();

    int f = steuerwerk->getRam()->lesen(befehl & 0x007f);
    int c = Bitoperationen::pruefeBit(Ram::STATUS, 0);

    int ergebnis = (((f << 1) & 0x00fe) + c);

    if (f & 0x80)
        steuerwerk->getRam()->setzeCBit();
    else
        steuerwerk->getRam()->loescheCBit();

    if (Bitoperationen::pruefeBit(befehl,7) == ZURUECKLADENINF) // prüft wo das Ergebnis gespeichert werden soll
        steuerwerk->getRam()->schreiben(ergebnis, (befehl & 0x007f));

    else
        steuerwerk->getW()->schreiben(ergebnis, Speicher::NOADDRESS);

    steuerwerk->getLaufzeitZaehler()->zyklenInkrementieren(1);
}

// schiebt alle Bits eines gewählten Registers nach rechts, Carry-Bit wird eingeschoben
void Alu::ausfuehrenRRF(int befehl)
{
    zaehlerstandErhoehen();

    int f = steuerwerk->getRam()->lesen(befehl & 0x007f);
    int c = Bitoperationen::pruefeBit(Ram::STATUS, 0);

    int ergebnis = (((f >> 1) & 0x00ef) + (c << 7));

    if (f & 0x01)
        steuerwerk->getRam()->setzeCBit();
    else
        steuerwerk->getRam()->loescheCBit();

    if (Bitoperationen::pruefeBit(befehl,7) == ZURUECKLADENINF) // prüft wo das Ergebnis gespeichert werden soll
        steuerwerk->getRam()->schreiben(ergebnis, (befehl & 0x007f));

    else
        steuerwerk->getW()->schreiben(ergebnis, Speicher::NOADDRESS);

    steuerwerk->getLaufzeitZaehler()->zyklenInkrementieren(1);
}

// subtrahiert ein gewähltes Registers vom W-Register
void Alu::ausfuehrenSUBWF(int befehl)
{
    zaehlerstandErhoehen();

    int f = steuerwerk->getRam()->lesen(befehl & 0x007f);
    int w = steuerwerk->getW()->lesen(Speicher::NOADDRESS);
    int ergebnis = f - w;

    if (pruefeCarry(ergebnis))
        steuerwerk->getRam()->setzeCBit();
    else
        steuerwerk->getRam()->loescheCBit();

    if (pruefeZero(ergebnis))
        steuerwerk->getRam()->setzeZBit();
    else
        steuerwerk->getRam()->loescheZBit();

    if (pruefeDigitCarry(f,w))
        steuerwerk->getRam()->setzeDCBit();
    else
        steuerwerk->getRam()->loescheDCBit();

    if (Bitoperationen::pruefeBit(befehl,7) == ZURUECKLADENINF) // prüft wo das Ergebnis gespeichert werden soll
        steuerwerk->getRam()->schreiben(ergebnis, (befehl & 0x007f));
    else
        steuerwerk->getW()->schreiben(ergebnis, Speicher::NOADDRESS);

    steuerwerk->getLaufzeitZaehler()->zyklenInkrementieren(1);
}

// tauscht die oberen 4 Bits mit den unteren 4 bits eines gewählten Registers
void Alu::ausfuehrenSWAPF(int befehl)
{
    zaehlerstandErhoehen();

    int f = steuerwerk->getRam()->lesen(befehl & 0x007f);
    int f_oben = ((f & 0xf0) >> 4);
    int f_unten = ((f & 0x0f) << 4);
    int ergebnis = f_unten + f_oben;

    steuerwerk->getRam()->schreiben(ergebnis, (befehl & 0x007f));

    steuerwerk->getLaufzeitZaehler()->zyklenInkrementieren(1);
}

// Bitweises exklusiv-oder eines gewählten Registers
void Alu::ausfuehrenXORWF(int befehl)
{
    zaehlerstandErhoehen();

    int f = steuerwerk->getRam()->lesen(befehl & 0x007f);
    int w = steuerwerk->getW()->lesen(Speicher::NOADDRESS);
    int ergebnis = (f ^ w);

    if (pruefeZero(ergebnis))
        steuerwerk->getRam()->setzeZBit();
    else
        steuerwerk->getRam()->loescheZBit();

    if (Bitoperationen::pruefeBit(befehl,7) == ZURUECKLADENINF) // prüft wo das Ergebnis gespeichert werden soll
        steuerwerk->getRam()->schreiben(ergebnis, (befehl & 0x007f));
    else
        steuerwerk->getW()->schreiben(ergebnis, Speicher::NOADDRESS);

    steuerwerk->getLaufzeitZaehler()->zyklenInkrementieren(1);
}

// löscht ein bestimmtes Bit eines gewählten Registers
void Alu::ausfuehrenBCF(int befehl)
{
    zaehlerstandErhoehen();

    int f = steuerwerk->getRam()->lesen(befehl & 0x007f);
    int b = ((befehl & 0x0380) >> 7);

    steuerwerk->getRam()->schreiben(Bitoperationen::loescheBit(f,b), (befehl & 0x007f));

    steuerwerk->getLaufzeitZaehler()->zyklenInkrementieren(1);
}

// setzt ein bestimmtes Bit eines gewählten Registers
void Alu::ausfuehrenBSF(int befehl)
{
    zaehlerstandErhoehen();

    int f = steuerwerk->getRam()->lesen(befehl & 0x007f);
    int b = ((befehl & 0x0380) >> 7);

    steuerwerk->getRam()->schreiben(Bitoperationen::setzeBit(f,b), (befehl & 0x007f));

    steuerwerk->getLaufzeitZaehler()->zyklenInkrementieren(1);
}

// prüft ein bestimmmtes Bit eines gewählten Registers, ist es 0 wird der nächste Befehl übersprungen
void Alu::ausfuehrenBTFSC(int befehl)
{
    zaehlerstandErhoehen();

    int f = steuerwerk->getRam()->lesen(befehl & 0x007f);
    int b = ((befehl & 0x0380) >> 7);

    if (Bitoperationen::zeigeBit(f,b) == 0)
    {
        zaehlerstandErhoehen();
        steuerwerk->getLaufzeitZaehler()->zyklenInkrementieren(1);
    }

    else
        steuerwerk->getLaufzeitZaehler()->zyklenInkrementieren(2);
}

// prüft ein bestimmmtes Bit eines gewählten Registers, ist es 1 wird der nächste Befehl übersprungen
void Alu::ausfuehrenBTFSS(int befehl)
{
    zaehlerstandErhoehen();

    int f = steuerwerk->getRam()->lesen(befehl & 0x007f);
    int b = ((befehl & 0x0380) >> 7);

    if (Bitoperationen::zeigeBit(f,b) == 1)
    {
        zaehlerstandErhoehen();
        steuerwerk->getLaufzeitZaehler()->zyklenInkrementieren(1);
    }

    else
        steuerwerk->getLaufzeitZaehler()->zyklenInkrementieren(2);}

// addiert ein bestimmten Wert zum W-Register
void Alu::ausfuehrenADDLW(int befehl)
{
    zaehlerstandErhoehen();

    int konstante = (befehl & 0x00ff);
    int w = steuerwerk->getW()->lesen(Speicher::NOADDRESS);
    int ergebnis = konstante + w;

    if (pruefeCarry(ergebnis))
        steuerwerk->getRam()->setzeCBit();
    else
        steuerwerk->getRam()->loescheCBit();

    if (pruefeZero(ergebnis))
        steuerwerk->getRam()->setzeZBit();
    else
        steuerwerk->getRam()->loescheZBit();

    if (pruefeDigitCarry(konstante,w))
        steuerwerk->getRam()->setzeDCBit();
    else
        steuerwerk->getRam()->loescheDCBit();

    steuerwerk->getW()->schreiben(ergebnis,Speicher::NOADDRESS);

    steuerwerk->getLaufzeitZaehler()->zyklenInkrementieren(1);
}

// Verundung einer Konstanten mit dem W-Register
void Alu::ausfuehrenANDLW(int befehl)
{
    zaehlerstandErhoehen();

    int konstante = (befehl & 0x00ff);
    int w = steuerwerk->getW()->lesen(Speicher::NOADDRESS);
    int ergebnis = (konstante & w);

    if (pruefeZero(ergebnis))
        steuerwerk->getRam()->setzeZBit();
    else
        steuerwerk->getRam()->loescheZBit();

    steuerwerk->getW()->schreiben(ergebnis,Speicher::NOADDRESS);

    steuerwerk->getLaufzeitZaehler()->zyklenInkrementieren(1);
}

// ruft ein Unterprogramm auf
void Alu::ausfuehrenCALL(int befehl)
{
    int ruecksprungAdresse = steuerwerk->getProgrammzaehler()->lesen(Speicher::NOADDRESS)+1;
    steuerwerk->getStack()->schreiben(ruecksprungAdresse,Speicher::NOADDRESS);

    int sprungadresse = sprungadresseBerechnen(befehl);
    steuerwerk->getProgrammzaehler()->schreiben(sprungadresse,Speicher::NOADDRESS);

    steuerwerk->getLaufzeitZaehler()->zyklenInkrementieren(2);
}

// setzt den Watchdog zurück
void Alu::ausfuehrenCLRWDT(int befehl)
{
    zaehlerstandErhoehen();

    steuerwerk->getLaufzeitZaehler()->zyklenInkrementieren(1);
}

// führt einen Sprungbefehl aus
void Alu::ausfuehrenGOTO(int befehl)
{

    int sprungadresse = sprungadresseBerechnen(befehl);

    steuerwerk->getProgrammzaehler()->schreiben(sprungadresse,Speicher::NOADDRESS);

    steuerwerk->getLaufzeitZaehler()->zyklenInkrementieren(2);
}

// entweder-oder einer Konstanten und dem W-Register
void Alu::ausfuehrenIORLW(int befehl)
{
    zaehlerstandErhoehen();

    int konstante = (befehl & 0x00ff);
    int w = steuerwerk->getW()->lesen(Speicher::NOADDRESS);
    int ergebnis = (konstante | w);

    if (pruefeZero(ergebnis))
        steuerwerk->getRam()->setzeZBit();
    else
        steuerwerk->getRam()->loescheZBit();

    steuerwerk->getW()->schreiben(ergebnis,Speicher::NOADDRESS);

    steuerwerk->getLaufzeitZaehler()->zyklenInkrementieren(1);
}

// schreibt eine Konstante in das W-Register
void Alu::ausfuehrenMOVLW(int befehl)
{
    zaehlerstandErhoehen();

    int konstante = (befehl & 0x00ff);

    steuerwerk->getW()->schreiben(konstante,Speicher::NOADDRESS);

    steuerwerk->getLaufzeitZaehler()->zyklenInkrementieren(1);
}

void Alu::ausfuehrenRETFIE(int befehl)
{
    zaehlerstandErhoehen();

    // oberste Adresse vom Stack holen und zurückgeben, dann pop
    int ruecksprungadresse = steuerwerk->getStack()->lesen(Speicher::NOADDRESS);
    steuerwerk->getProgrammzaehler()->schreiben(ruecksprungadresse, Speicher::NOADDRESS);

    // GIE-Flag auf 1 setzen
    steuerwerk->getInterruptSteuerung()->setGIEFlag();

    steuerwerk->getLaufzeitZaehler()->zyklenInkrementieren(2);
}

// schreibt eine Konstante in das W-Register und springt zur obersten Adresse auf dem Stack
void Alu::ausfuehrenRETLW(int befehl)
{
    zaehlerstandErhoehen();

    int konstante = (befehl & 0xff);

    steuerwerk->getW()->schreiben(konstante,Speicher::NOADDRESS);

    //oberste Adresse vom Stack holen und zurückgeben, dann pop
    int ruecksprungadresse = steuerwerk->getStack()->lesen(Speicher::NOADDRESS);
    steuerwerk->getProgrammzaehler()->schreiben(ruecksprungadresse, Speicher::NOADDRESS);

    steuerwerk->getLaufzeitZaehler()->zyklenInkrementieren(2);
}

// springt zur obersten Adresse auf dem Stack
void Alu::ausfuehrenRETURN(int befehl)
{
    zaehlerstandErhoehen();

    int ruecksprungadresse = steuerwerk->getStack()->lesen(Speicher::NOADDRESS);
    steuerwerk->getProgrammzaehler()->schreiben(ruecksprungadresse, Speicher::NOADDRESS);

    steuerwerk->getLaufzeitZaehler()->zyklenInkrementieren(2);
}

// führt eines Schlaf-Befehl aus // MUSS NOCH IMPLEMENTIERT WERDEN !! //
void Alu::ausfuehrenSLEEP(int befehl)
{
    steuerwerk->getLaufzeitZaehler()->zyklenInkrementieren(1);
}

// subtrahiert eine Konstante vom W-Register
void Alu::ausfuehrenSUBLW(int befehl)
{
    zaehlerstandErhoehen();

    int konstante = (befehl & 0x00ff);
    int w = steuerwerk->getW()->lesen(Speicher::NOADDRESS);
    int ergebnis = konstante - w;

    if (pruefeCarry(ergebnis))
        steuerwerk->getRam()->setzeCBit();
    else
        steuerwerk->getRam()->loescheCBit();

    if (pruefeZero(ergebnis))
        steuerwerk->getRam()->setzeZBit();
    else
        steuerwerk->getRam()->loescheZBit();

    if (pruefeDigitCarry(konstante,w))
        steuerwerk->getRam()->setzeDCBit();
    else
        steuerwerk->getRam()->loescheDCBit();

    steuerwerk->getW()->schreiben(ergebnis,Speicher::NOADDRESS);

    steuerwerk->getLaufzeitZaehler()->zyklenInkrementieren(1);
}

// exklusiv-oder einer Konstanten und des W-Registers
void Alu::ausfuehrenXORLW(int befehl)
{
    zaehlerstandErhoehen();

    int konstante = (befehl & 0x00ff);
    int w = steuerwerk->getW()->lesen(Speicher::NOADDRESS);
    int ergebnis = (konstante ^ w);

    if (pruefeZero(ergebnis))
        steuerwerk->getRam()->setzeZBit();
    else
        steuerwerk->getRam()->loescheZBit();

    steuerwerk->getW()->schreiben(ergebnis,Speicher::NOADDRESS);

    steuerwerk->getLaufzeitZaehler()->zyklenInkrementieren(1);
}

// berechnet die aktuelle Rücksprungadresse
int Alu::sprungadresseBerechnen(int befehl)
{
    int konstante = (befehl & 0x7ff);
    int pclath = steuerwerk->getRam()->lesen(0x0A);
    pclath = (pclath & 0x18) << 8;
    int sprungadresse = (pclath | konstante);

    return sprungadresse;
}

// prüft das Carry-Bit
bool Alu::pruefeCarry(int ergebnis)
{
    return (ergebnis >= 0x100);
}

// prüft das Zero-Bit
bool Alu::pruefeZero(int ergebnis)
{
    return ((ergebnis & 0x00ff) == 0);
}

// prüft das Digit-Carry-Bit
bool Alu::pruefeDigitCarry(int konstante, int w)
{
    int ergebnis = (konstante & 0x000f) + (w & 0x000f);
    return (ergebnis >= 0x10);
}
