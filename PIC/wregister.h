#ifndef WREGISTER_H
#define WREGISTER_H

#include "speicher.h"

class Wregister : public Speicher
{
public:
    Wregister();
    int lesen(int adresse);
    void schreiben(int wert, int adresse);

private:
    int w;
};

#endif // WREGISTER_H
