#include "wregister.h"

Wregister::Wregister()
{
    w = 0;
}

//Auslesen des Wertes im W-Register
int Wregister::lesen(int adresse)
{
    return w;
}

//Schreiben des Wertes im W-Register
void Wregister::schreiben(int wert, int adresse)
{
    w = wert & 0xff;
}
