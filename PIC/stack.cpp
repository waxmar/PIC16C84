#include "stack.h"

Stack::Stack()
{
}

int Stack::lesen(int adresse)
{
    if (stack.isEmpty())
        return 0x1000;
    int ruecksprungAdresse = stack.last();
    stack.removeLast();
    return ruecksprungAdresse;
}

void Stack::schreiben(int wert, int adresse)
{
    stack.append(wert);
}

QList<int>* Stack::getInhalt(void)
{
    return &stack;
}
