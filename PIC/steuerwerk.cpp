#include "steuerwerk.h"
#include "mainwindow.h"

#include "codezeile.h"
#include "programmspeicher.h"
#include "programmzaehler.h"
#include "alu.h"
#include "ram.h"
#include "stack.h"
#include "laufzeitzaehler.h"
#include "timersteuerung.h"
#include "interruptsteuerung.h"
#include "wregister.h"

#include <iostream>

Steuerwerk::Steuerwerk(MainWindow* gui)
{
    this->gui = gui;
    programmspeicher = new Programmspeicher();
    programmzaehler = new Programmzaehler();
    alu = new Alu(this);
    ram = new Ram(this);
    stack = new Stack();
    w = new Wregister();
    laufzeit = new LaufzeitZaehler(this);
    timerSteuerung = new TimerSteuerung(this);
    InterruptSteuerung = new InterruptSteuerung(this);
}

Programmspeicher* Steuerwerk::getProgrammspeicher()
{
    return programmspeicher;

}

Programmzaehler* Steuerwerk::getProgrammzaehler()
{
    return programmzaehler;
}

Ram* Steuerwerk::getRam()
{
    return ram;
}

Stack* Steuerwerk::getStack()
{
    return stack;
}

Alu* Steuerwerk::getAlu()
{
    return alu;
}

Wregister* Steuerwerk::getW()
{
    return w;
}

//Steuerung eines einzelnen Schrittes (Zählerstand erhöhen, Befehl lesen - parsen - ausführen, Oberfläche aktualiseren)
void Steuerwerk::schrittSteuern()
{
    gui->fokusAlteProgrammzeileEntfernen();

    int zaehlerstand = programmzaehler->lesen(-1);
    int befehl = programmspeicher->lesen(zaehlerstand);

    befehlErkennen(befehl);

    ram->schreiben(programmzaehler->lesen(Speicher::NOADDRESS), Ram::PCL, 0);

    gui->erneuernUI();
}

LaufzeitZaehler* Steuerwerk::getLaufzeitZaehler()
{
    return laufzeit;
}

TimerSteuerung* Steuerwerk::getTimerSteuerung()
{
    return timerSteuerung;
}

InterruptSteuerung* Steuerwerk::getInterruptSteuerung()
{
    return InterruptSteuerung;
}

void Steuerwerk::befehlErkennen(int befehl)
{
    // ADDWF parsen
    if((befehl & 0x3f00) == 0x0700)
        alu->ausfuehrenADDWF(befehl);

    // ANDWF parsen
    if((befehl & 0x3f00) == 0x0500)
        alu->ausfuehrenANDWF(befehl);

    // CLRF parsen
    if((befehl & 0x3f80) == 0x0180)
        alu->ausfuehrenCLRF(befehl);

    // CLRW parsen
    if((befehl & 0x3f80) == 0x0100)
        alu->ausfuehrenCLRW(befehl);

    // COMF parsen
    if((befehl & 0x3f00) == 0x0900)
        alu->ausfuehrenCOMF(befehl);

    // DECF parsen
    if((befehl & 0x3f00) == 0x0300)
        alu->ausfuehrenDECF(befehl);

    // DECFSZ parsen
    if((befehl & 0x3f00) == 0x0b00)
        alu->ausfuehrenDECFSZ(befehl);

    // INCF parsen
    if((befehl & 0x3f00) == 0x0a00)
        alu->ausfuehrenINCF(befehl);

    // INCFSZ parsen
    if((befehl & 0x3f00) == 0x0f00)
        alu->ausfuehrenINCFSZ(befehl);

    // IORWF parsen
    if((befehl & 0x3f00) == 0x0400)
        alu->ausfuehrenIORWF(befehl);

    // MOVF parsen
    if((befehl & 0x3f00) == 0x0800)
        alu->ausfuehrenMOVF(befehl);

    // MOVWF parsen
    if((befehl & 0x3f80) == 0x0080)
        alu->ausfuehrenADDWF(befehl);

    // NOP parsen
    if((befehl & 0x3f9f) == 0)
        alu->ausfuehrenNOP();

    // RLF parsen
    if((befehl & 0x3f00) == 0x0d00)
        alu->ausfuehrenRLF(befehl);

    // RRF parsen
    if((befehl & 0x3f00) == 0x0c00)
        alu->ausfuehrenRRF(befehl);

    // SUBWF parsen
    if((befehl & 0x3f00) == 0x0200)
        alu->ausfuehrenSUBWF(befehl);

    // SWAPF parsen
    if((befehl & 0x3f00) == 0x0e00)
        alu->ausfuehrenSWAPF(befehl);

    // XORWF parsen
    if((befehl & 0x3f00) == 0x0600)
        alu->ausfuehrenXORWF(befehl);

    // BCF parsen
    if((befehl & 0x3c00) == 0x1000)
        alu->ausfuehrenBCF(befehl);

    // BSF parsen
    if((befehl & 0x3c00) == 0x1400)
        alu->ausfuehrenBSF(befehl);

    // BTFSC parsen
    if((befehl & 0x3c00) == 0x1800)
        alu->ausfuehrenBTFSC(befehl);

    // BTFSS parsen
    if((befehl & 0x3c00) == 0x1c00)
        alu->ausfuehrenBTFSS(befehl);

    // ADDLW parsen
    if((befehl & 0x3e00) == 0x3e00)
        alu->ausfuehrenADDLW(befehl);

    // ANDLW parsen
    if((befehl & 0x3f00) == 0x3900)
        alu->ausfuehrenANDLW(befehl);

    // CALL parsen
    if((befehl & 0x3800) == 0x2000)
        alu->ausfuehrenCALL(befehl);

    // CLRWDT parsen
    if((befehl & 0x3fff) == 0x0064)
        alu->ausfuehrenCLRWDT(befehl);

    // GOTO parsen
    if((befehl & 0x3800) == 0x2800)
        alu->ausfuehrenGOTO(befehl);

    // IORLW parsen
    if((befehl & 0x3f00) == 0x3800)
        alu->ausfuehrenIORLW(befehl);

    // MOVLW parsen
    if((befehl & 0x3a00) == 0x3000)
        alu->ausfuehrenMOVLW(befehl);

    // RETFIE parsen
    if((befehl & 0x3fff) == 0x0009)
        alu->ausfuehrenRETFIE(befehl);

    // RETLW parsen
    if((befehl & 0x3c00) == 0x3400)
        alu->ausfuehrenRETLW(befehl);

    // RETURN parsen
    if((befehl & 0x3fff) == 0x0008)
        alu->ausfuehrenRETURN(befehl);

    // SLEEP parsen
    if((befehl & 0x3fff) == 0x0063)
        alu->ausfuehrenSLEEP(befehl);

    // SUBLW parsen
    if((befehl & 0x3e00) == 0x3c00)
        alu->ausfuehrenSUBLW(befehl);

    // XORLW parsen
    if((befehl & 0x3f00) == 0x3a00)
        alu->ausfuehrenXORLW(befehl);
}
