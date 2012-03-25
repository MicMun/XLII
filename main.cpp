#include "mainwindow.h"

#include <QtGui/QApplication>
#include <QTextCodec>

int main(int argc, char *argv[])
{
   QApplication app(argc, argv);
   // language to use
   QTranslator editTranslator;
   QString fileName;
   fileName = QString(":/mytr_%1").arg(QLocale::system().name());
   editTranslator.load(fileName, qApp->applicationDirPath());
   app.installTranslator(&editTranslator);
   // Codec is always UTF-8
   QTextCodec::setCodecForTr(QTextCodec::codecForName("utf-8"));
   QTextCodec::setCodecForCStrings(QTextCodec::codecForName("utf-8"));
   QTextCodec::setCodecForLocale(QTextCodec::codecForName("utf-8"));
   MainWindow mainWindow;
   mainWindow.setOrientation(MainWindow::ScreenOrientationAuto);
   mainWindow.showExpanded();

   return app.exec();
}
