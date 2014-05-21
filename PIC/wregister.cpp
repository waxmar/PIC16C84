#include "wregister.h"

Wregister::Wregister()
{
    w = 0;
}

int Wregister::lesen(int adresse)
{
    return w;
}

void Wregister::schreiben(int wert, int adresse)
{
    w = wert & 0xff;
}
