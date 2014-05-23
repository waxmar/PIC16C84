#ifndef INTERRUPTSTEUERUNG_H
#define INTERRUPTSTEUERUNG_H

class Steuerwerk;

class InterruptSteuerung
{
public:
    InterruptSteuerung(Steuerwerk* steuerwerk);

private:
    Steuerwerk* steuerwerk;
};

#endif // INTERRUPTSTEUERUNG_H
