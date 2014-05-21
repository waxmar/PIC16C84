#include "ram.h"
#include <stdlib.h>

Ram::Ram()
{


    for (int i=0; i<0x50;i++)
    {
        // Alle Adressen zeigen auf Bank 0
        adressen[0][i]=&bank0[i];
        adressen[1][i]=&bank0[i];

        bank0[i] = 0;
        bank1[i] = 0;
    }

    //Definition der Adressen auf Bank 1 S.6

    adressen[1][0x01] = &bank1[0x01];
    adressen[1][0x05] = &bank1[0x05];
    adressen[1][0x06] = &bank1[0x06];
    adressen[1][0x08] = &bank1[0x08];
    adressen[1][0x09] = &bank1[0x09];
    adressen[0][0x07] = NULL;
    adressen[1][0x07] = NULL;


    // Defaultwerte für Speicher initialisieren!
}

int Ram::lesen(int adresse)
{
int aktiveBank = getActiveBank();
if (adressen[aktiveBank][adresse]==NULL)
    return 256;
return *adressen[aktiveBank][adresse];

}


void Ram::schreiben(int wert, int adresse)
{
    int aktiveBank = getActiveBank();
    if (adressen[aktiveBank][adresse]==NULL)
return;
     *adressen[aktiveBank][adresse] = (wert&0xff);
}


int Ram::getActiveBank()
{
return (bank0[0x03]&0x20>>5);

}
