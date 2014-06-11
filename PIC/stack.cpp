#include "stack.h"

Stack::Stack()
{
}

//Auslesen des Stackinhaltes
int Stack::lesen(int adresse)
{
    if (stack.isEmpty())
        return 0x1000;
    int ruecksprungAdresse = stack.last();
    stack.removeLast();
    return ruecksprungAdresse;
}

//Legt eine Rücksprungadresse auf den Stack
void Stack::schreiben(int wert, int adresse)
{
    stack.append(wert);
}

//L�scht die Stackinhalte
void Stack::loeschen()
{
    stack.clear();
}

//Gibt die Adresse des Stack zurück
QList<int>* Stack::getInhalt(void)
{
    return &stack;
}
