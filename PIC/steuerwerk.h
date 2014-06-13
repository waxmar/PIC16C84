#ifndef STEUERWERK_H
#define STEUERWERK_H

#include <QList>

class MainWindow;
class Codezeile;
class Programmspeicher;
class Programmzaehler;
class Alu;
class Ram;
class Stack;
class Wregister;
class LaufzeitZaehler;
class TimerSteuerung;
class InterruptSteuerung;

class Steuerwerk
{
public:
    Steuerwerk(MainWindow* gui);
    MainWindow* gui;
    Programmspeicher* getProgrammspeicher();
    Programmzaehler* getProgrammzaehler();
    Ram* getRam();
    Stack* getStack();
    Alu* getAlu();
    Wregister* getW();
    LaufzeitZaehler* getLaufzeitZaehler();
    TimerSteuerung* getTimerSteuerung();
    InterruptSteuerung* getInterruptSteuerung();

    void schrittSteuern();

private:
    Programmspeicher* programmspeicher;
    Programmzaehler* programmzaehler;
    Alu* alu;
    Ram* ram;
    Stack* stack;
    Wregister* w;
    LaufzeitZaehler* laufzeit;
    TimerSteuerung* timerSteuerung;
    InterruptSteuerung* interruptSteuerung;

    void befehlErkennen(int befehl);
};

#endif // STEUERWERK_H
