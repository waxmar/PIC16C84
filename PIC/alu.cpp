#include "alu.h"
#include "programmzaehler.h"
#include "steuerwerk.h"
#include "ram.h"
#include "stack.h"

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

}

void Alu::ausfuehrenANDWF(int befehl)
{

}

void Alu::ausfuehrenCLRF(int befehl)
{

}

void Alu::ausfuehrenCLRW(int befehl)
{

}

void Alu::ausfuehrenCOMF(int befehl)
{
    befehl = ~befehl;

    std::cout << "Komplement = " << befehl << std::endl;
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

}

void Alu::ausfuehrenANDLW(int befehl)
{

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
