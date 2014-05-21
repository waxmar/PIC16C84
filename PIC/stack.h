#ifndef STACK_H
#define STACK_H

#include "speicher.h"
#include <QList>

class Stack : public Speicher
{
public:
    Stack();
    int lesen(int adresse);
    void schreiben(int wert, int adresse);
    QList<int>* getInhalt(void);

private:
    QList<int> stack;
};

#endif // STACK_H
