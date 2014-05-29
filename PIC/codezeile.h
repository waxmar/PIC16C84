#ifndef CODEZEILE_H
#define CODEZEILE_H

class Codezeile
{
public:
    Codezeile(int befehl, int textZeile);

    int getBefehl();
    bool isBreakpoint();
    int getTextzeile();
    void toggleBreakpoint();

private:
    int befehl;
    bool breakpoint;
    int textZeile;

};

#endif // CODEZEILE_H
