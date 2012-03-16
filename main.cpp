#include "mainwindow.h"

#include <QtGui/QApplication>
#include <QTextCodec>

int main(int argc, char *argv[])
{
   QApplication app(argc, argv);
   QTextCodec::setCodecForTr(QTextCodec::codecForName("utf-8"));
   QTextCodec::setCodecForCStrings(QTextCodec::codecForName("utf-8"));
   QTextCodec::setCodecForLocale(QTextCodec::codecForName("utf-8"));
   MainWindow mainWindow;
   mainWindow.setOrientation(MainWindow::ScreenOrientationAuto);
   mainWindow.showExpanded();

   return app.exec();
}
