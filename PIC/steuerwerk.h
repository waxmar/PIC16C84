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

class Steuerwerk
{
public:
    Steuerwerk(MainWindow* gui);
    MainWindow* gui;
    Programmspeicher* getProgrammspeicher();
    Programmzaehler* getProgrammzaehler();
    Ram* getRam();
    Stack* getStack();
    Wregister* getW();
    void schrittSteuern();

private:
    Programmspeicher* programmspeicher;
    Programmzaehler* programmzaehler;
    Alu* alu;
    Ram* ram;
    Stack* stack;
    Wregister* w;
    void befehlErkennen(int befehl);
};

#endif // STEUERWERK_H
