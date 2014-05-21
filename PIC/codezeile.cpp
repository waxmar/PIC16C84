#include "codezeile.h"

Codezeile::Codezeile(int befehl, int textZeile)
{
    this->befehl = befehl;
    this->textZeile = textZeile;
    this->breakpoint = false;

}

int Codezeile::getBefehl()
{
    return befehl;
}

bool Codezeile::isBreakpoint()
{
    return breakpoint;
}

int Codezeile::getTextzeile()
{
    return textZeile;
}
