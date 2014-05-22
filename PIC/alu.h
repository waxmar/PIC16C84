#ifndef ALU_H
#define ALU_H

class Steuerwerk;

class Alu
{
public:
    Alu(Steuerwerk* steuerwerk);

    void ausfuehrenADDWF(int befehl);
    void ausfuehrenANDWF(int befehl);
    void ausfuehrenCLRF(int befehl);
    void ausfuehrenCLRW(int befehl);
    void ausfuehrenCOMF(int befehl);
    void ausfuehrenDECF(int befehl);
    void ausfuehrenDECFSZ(int befehl);
    void ausfuehrenINCF(int befehl);
    void ausfuehrenINCFSZ(int befehl);
    void ausfuehrenIORWF(int befehl);
    void ausfuehrenMOVF(int befehl);
    void ausfuehrenMOVWF(int befehl);
    void ausfuehrenNOP(void);
    void ausfuehrenRLF(int befehl);
    void ausfuehrenRRF(int befehl);
    void ausfuehrenSUBWF(int befehl);
    void ausfuehrenSWAPF(int befehl);
    void ausfuehrenXORWF(int befehl);

    void ausfuehrenBCF(int befehl);
    void ausfuehrenBSF(int befehl);
    void ausfuehrenBTFSC(int befehl);
    void ausfuehrenBTFSS(int befehl);

    void ausfuehrenADDLW(int befehl);
    void ausfuehrenANDLW(int befehl);
    void ausfuehrenCALL(int befehl);
    void ausfuehrenCLRWDT(int befehl);
    void ausfuehrenGOTO(int befehl);
    void ausfuehrenIORLW(int befehl);
    void ausfuehrenMOVLW(int befehl);
    void ausfuehrenRETFIE(int befehl);
    void ausfuehrenRETLW(int befehl);
    void ausfuehrenRETURN(int befehl);
    void ausfuehrenSLEEP(int befehl);
    void ausfuehrenSUBLW(int befehl);
    void ausfuehrenXORLW(int befehl);

    void zaehlerstandErhoehen();
    int sprungadresseBerechnen(int befehl);

    bool pruefeCarry(int ergebnis);
    bool pruefeZero(int ergebnis);
    bool pruefeDigitCarry(int konstante, int w);

private:
    Steuerwerk* steuerwerk;

    static const bool STOREBACKINF = true;
};

#endif // ALU_H
