#include "hexconverter.h"

HexConverter::HexConverter()
{
}

QString HexConverter::intToHex(int wert)
{
    int mask = 0x00f0; // entspricht 0b11110000
   QString sresult;

   for(int schleife = 0; schleife < 2;schleife++)
   {

       int nibble=wert & mask;
       if(0==schleife) nibble >>= 4;
       switch (nibble) {
       case 0:
           sresult.append('0');
           break;
       case 1:
           sresult.append('1');
           break;
       case 2:
           sresult.append('2');
           break;
       case 3:
           sresult.append('3');
           break;
       case 4:
           sresult.append('4');
           break;
       case 5:
           sresult.append('5');
           break;
       case 6:
           sresult.append('6');
           break;
       case 7:
           sresult.append('7');
           break;
       case 8:
           sresult.append('8');
           break;
       case 9:
           sresult.append('9');
           break;
       case 10:
           sresult.append('A');
           break;
       case 11:
           sresult.append('B');
           break;
       case 12:
           sresult.append('C');
           break;
       case 13:
           sresult.append('D');
           break;
       case 14:
           sresult.append('E');
           break;
       case 15:
           sresult.append('F');
           break;
       default:
           break;
       }
       mask=mask>>4;
   }

   return sresult;
}
