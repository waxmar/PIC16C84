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

class Steuerwerk
{
public:
    Steuerwerk(MainWindow* gui);
    MainWindow* gui;
    Programmspeicher* getProgrammspeicher();
    Programmzaehler* getProgrammzaehler();
    Ram* getRam();
    Stack* getStack();
    void schrittSteuern();

private:
    Programmspeicher* programmspeicher;
    Programmzaehler* programmzaehler;
    Alu* alu;
    Ram* ram;
    Stack* stack;
    void befehlErkennen(int befehl);
};

#endif // STEUERWERK_H
