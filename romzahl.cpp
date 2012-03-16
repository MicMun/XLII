#include "romzahl.h"

RomZahl::RomZahl()
{
   arabian = 0;
   toRom();
}

RomZahl::RomZahl(int z)
{
   arabian = z;
   toRom();
}

RomZahl::RomZahl(QString r)
{
   roman = r;
   toArabian();
   toRom();
}

QString RomZahl::getArabian()
{
   return QString::number(arabian);
}

QString RomZahl::getRom()
{
   return roman;
}

void RomZahl::toArabian() throw (QString)
{
   int j;
   char romZiffern[] = {'i', 'v', 'x', 'l', 'c', 'd', 'm'};
   char romZiffernUP[] = {'I', 'V', 'X', 'L', 'C', 'D', 'M'};
   int ziffern[] = {1, 5, 10, 50, 100, 500, 1000};
   int* hilfe = new int[10];

   if (roman.at(0) == '0') return;

   int stellen;
   for (stellen = 0; stellen < roman.length(); stellen++) {
      for (j = 0; j < 7; j++)
         if (roman.at(stellen) == romZiffern[j] ||
             roman.at(stellen) == romZiffernUP[j]) {
            hilfe[stellen] = ziffern[j];
            break;
         }
      if (j == 7)
         throw("FEHLER: Keine gueltige roemische Zahl {" + roman + "}");
   }

   for (j = 1; j < stellen; j++)
      if (hilfe[j] > hilfe[j-1]) {
         hilfe[j] -= hilfe[j-1];
         hilfe[j-1] = 0;
      }

   arabian = 0;
   for (j = 0; j < stellen; j++) arabian += hilfe[j];
}

void RomZahl::toRom()
{
   QString roemZiffern[] = {"M", "CM", "D", "CD", "C", "XC", "L", "XL",
                            "X", "IX", "V", "IV", "I"};
   int ziffern[] = {1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1};
   int zahl, i = 0;

   zahl = arabian;
   roman = "";
   while (zahl > 0) {
      if (zahl/ziffern[i] >= 1) {
         roman += roemZiffern[i];
         zahl -= ziffern[i];
      } else {
         i++;
      }
   }
}
