#ifndef ALU_H
#define ALU_H

class Steuerwerk;

class Alu
{
public:
    Alu(Steuerwerk* steuerwerk);

    void ausfuehrenNOP(void);
    void ausfuehrenCALL(int befehl);
    void ausfuehrenGOTO(int befehl);

    void zaehlerstandErhoehen();
    int sprungadresseBerechnen(int befehl);

private:
    Steuerwerk* steuerwerk;
};

#endif // ALU_H
