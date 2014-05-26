#include "bitoperationen.h"

Bitoperationen::Bitoperationen()
{
}

//prüft ob ein bestimmtes Bit auf 1 gesetzt ist
bool Bitoperationen::pruefeBit(int wert, int bit)
{
    return ((wert >> bit) & 0x01);
}

//setzt ein bestimmtes Bit auf 0
int Bitoperationen::loescheBit(int wert, int bit)
{
    return (~(1 << bit) & wert);
}

//setzt ein bestimmtes Bit auf 1
int Bitoperationen::setzeBit(int wert, int bit)
{
    return ((1 << bit) | wert);
}
