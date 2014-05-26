#ifndef BITOPERATIONEN_H
#define BITOPERATIONEN_H

class Bitoperationen
{
public:
    Bitoperationen();

    static bool pruefeBit(int wert, int bit);
    static int loescheBit(int wert, int bit);
    static int setzeBit(int wert, int bit);
    static int zeigeBit(int wert, int bit);
    static int toggleBit(int wert);
};

#endif // BITOPERATIONEN_H
