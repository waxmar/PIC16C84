#include "steuerwerk.h"
#include "mainwindow.h"

#include "codezeile.h"
#include "programmspeicher.h"
#include "programmzaehler.h"
#include "alu.h"
#include "ram.h"
#include "stack.h"

#include <iostream>

Steuerwerk::Steuerwerk(MainWindow* gui)
{
    this->gui = gui;
    programmspeicher = new Programmspeicher();
    programmzaehler = new Programmzaehler();
    alu = new Alu(this);
    ram = new Ram();
    stack = new Stack();
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

void Steuerwerk::schrittSteuern()
{
    int zaehlerstand = programmzaehler->lesen(-1);
    int befehl = programmspeicher->lesen(zaehlerstand);

    befehlErkennen(befehl);

    gui->erneuernUI();
}

void Steuerwerk::befehlErkennen(int befehl)
{

    // NOP parsen
    if((befehl & 0x3f9f) == 0)
        alu->ausfuehrenNOP();

    // CALL parsen
    if((befehl & 0x3800) == 0x2000)
        alu->ausfuehrenCALL(befehl);

    // GOTO parsen
    if((befehl & 0x3800) == 0x2800)
        alu->ausfuehrenGOTO(befehl);
}
