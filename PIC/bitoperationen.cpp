#include "bitoperationen.h"

Bitoperationen::Bitoperationen()
{
}

bool Bitoperationen::pruefeBit(int wert, int bit)
{
    return ((wert >> bit) & 0x01);
}

int Bitoperationen::loescheBit(int wert, int bit)
{
    return (~(1 << bit) & wert);
}

int Bitoperationen::setzeBit(int wert, int bit)
{
    return ((1 << bit) | wert);
}
