#ifndef TIMERSTEUERUNG_H
#define TIMERSTEUERUNG_H

class Steuerwerk;

class TimerSteuerung
{
public:
    TimerSteuerung(Steuerwerk* steuerwerk);

    static const int notRBPU    = 7;
    static const int INTEDG     = 6;
    static const int T0CS       = 5;
    static const int T0SE       = 4;
    static const int PSA        = 3;
    static const int PS2        = 2;
    static const int PS1        = 1;
    static const int PS0        = 0;

    void handleTimer0();
private:
    Steuerwerk* steuerwerk;

    int* option_register;
    int* tmr0_register;
    int* ra_register;

    int psaTeiler;
    bool alterWertRA4;
    unsigned int anzahlGueltigerFlanken;

    int calculatePsaTeiler();
    bool externerTakt(int aktuellerWert);
    bool internerTakt();

    bool istFallendeFlanke(int aktuellerWert);
    bool istSteigendeFlanke(int aktuellerWert);

    void timerInkrementieren();
};

#endif // TIMERSTEUERUNG_H
