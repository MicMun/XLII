#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui>
#include <QtMaemo5/QMaemo5InformationBox>

namespace Ui {
   class MainWindow;
}

class MainWindow : public QMainWindow
{
   Q_OBJECT
public:
   enum ScreenOrientation {
      ScreenOrientationLockPortrait,
      ScreenOrientationLockLandscape,
      ScreenOrientationAuto
   };

   explicit MainWindow(QWidget *parent = 0);
   virtual ~MainWindow();

   // Note that this will only have an effect on Symbian and Fremantle.
   void setOrientation(ScreenOrientation orientation);

   void showExpanded();

private:
   Ui::MainWindow *ui;
private slots:
   void transform();
   void reset();
};

#endif // MAINWINDOW_H
