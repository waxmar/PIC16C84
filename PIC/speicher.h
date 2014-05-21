#ifndef SPEICHER_H
#define SPEICHER_H



class Speicher

{
public:
    Speicher();

    virtual int lesen(int adresse)=0;
    virtual void schreiben(int wert, int adresse)=0;

    static const int NOADDRESS = -1;

private:

};

#endif // SPEICHER_H
