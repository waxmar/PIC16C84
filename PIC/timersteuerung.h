#ifndef TIMERSTEUERUNG_H
#define TIMERSTEUERUNG_H

class Steuerwerk;

class TimerSteuerung
{
public:
    TimerSteuerung(Steuerwerk* steuerwerk);

private:
    Steuerwerk* steuerwerk;
};

#endif // TIMERSTEUERUNG_H
