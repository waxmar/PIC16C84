#ifndef WATCHDOG_H
#define WATCHDOG_H

class Steuerwerk;

class Watchdog
{
public:
    Watchdog(Steuerwerk* steuerwerk);
    void incrementWDT();
    void resetWDT();

private:
    Steuerwerk* steuerwerk;
    int psaTeiler;
    int timerValue;
    int calculatePsaTeiler();

    int* option_register;
};

#endif // WATCHDOG_H
