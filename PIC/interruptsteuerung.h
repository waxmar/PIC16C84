#ifndef INTERRUPTSTEUERUNG_H
#define INTERRUPTSTEUERUNG_H

class Steuerwerk;

class InterruptSteuerung
{
public:
    InterruptSteuerung(Steuerwerk* steuerwerk);

    void checkForInterrupt();

    static const int GIE = 7;
    static const int EEIE = 6;
    static const int T0IE = 5;
    static const int INTE = 4;
    static const int RBIE = 3;
    static const int T0IF = 2;
    static const int INTF = 1;
    static const int RBIF = 0;

    static const int INTERRUPT_ADDRESS = 0x0004;

private:
    Steuerwerk* steuerwerk;
    int* intcon_register;

    void interruptAusloesen();

    void timerInterrupt();
};

#endif // INTERRUPTSTEUERUNG_H
