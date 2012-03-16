#ifndef ROMZAHL_H
#define ROMZAHL_H

#include <QString>

class RomZahl
{
public:
   RomZahl();
   RomZahl(int z);
   RomZahl(QString r);

   QString getRom();
   QString getArabian();
private:
   int arabian;
   QString roman;

   void toArabian() throw(QString);
   void toRom();
};

#endif // ROMZAHL_H
