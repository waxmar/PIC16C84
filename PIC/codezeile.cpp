#include "codezeile.h"

Codezeile::Codezeile(int befehl, int textZeile)
{
    this->befehl = befehl;
    this->textZeile = textZeile;
    this->breakpoint = false;

}

//holt sich den Befehlscode aus der aktuellen Zeile
int Codezeile::getBefehl()
{
    return befehl;
}

//prüft ob in der aktuellen Zeile ein Breakpoint gesetzt wurde
bool Codezeile::isBreakpoint()
{
    return breakpoint;
}

//gibt die Nummer der aktuellen Zextzeile zurÃ¼ck
int Codezeile::getTextzeile()
{
    return textZeile;
}

void Codezeile::toggleBreakpoint()
{
    breakpoint = !breakpoint;
}
