#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QtCore/QCoreApplication>
#include "romzahl.h"

// Constructor: New MainWindow
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle(tr("XLII")); // Title

    // connects the button and the menu-item with the slots
    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(transform()));
    connect(ui->actionReset, SIGNAL(triggered()), this, SLOT(reset()));
}

// Destructor
MainWindow::~MainWindow()
{
    delete ui;
}

// Clears the input and the output fields
void MainWindow::reset()
{
   ui->lineEdit->setText(QString());
   ui->label->setText(QString("   "));
}

// Transforms the input in the way it will be selected.
void MainWindow::transform()
{
   QString in = ui->lineEdit->text();

   // arabian to roman number is selected
   if (ui->radioButton->isChecked() && !in.isNull() && !in.isEmpty()) {
      bool ok;
      int z = in.toInt(&ok); // input as number
      if (ok) {
         RomZahl r(z);
         ui->label->setText(r.getRom());
      } else {
         QMaemo5InformationBox::information (this, tr("Not a valid number"),
                                             1000);
      }
   // roman to arabian number is selected
   } else if (ui->radioButton_2->isChecked() && !in.isNull() && !in.isEmpty()) {
      try {
         RomZahl r(in);
         ui->label->setText(r.getArabian());
      } catch (QString msg) { // if no valid roman number
         QMaemo5InformationBox::information (this, msg, 1000);
      }
   }
}

void MainWindow::setOrientation(ScreenOrientation orientation)
{
#if defined(Q_OS_SYMBIAN)
    // If the version of Qt on the device is < 4.7.2, that attribute won't work
    if (orientation != ScreenOrientationAuto) {
        const QStringList v = QString::fromAscii(qVersion()).split(QLatin1Char('.'));
        if (v.count() == 3 && (v.at(0).toInt() << 16 | v.at(1).toInt() << 8 | v.at(2).toInt()) < 0x040702) {
            qWarning("Screen orientation locking only supported with Qt 4.7.2 and above");
            return;
        }
    }
#endif // Q_OS_SYMBIAN

    Qt::WidgetAttribute attribute;
    switch (orientation) {
#if QT_VERSION < 0x040702
    // Qt < 4.7.2 does not yet have the Qt::WA_*Orientation attributes
    case ScreenOrientationLockPortrait:
        attribute = static_cast<Qt::WidgetAttribute>(128);
        break;
    case ScreenOrientationLockLandscape:
        attribute = static_cast<Qt::WidgetAttribute>(129);
        break;
    default:
    case ScreenOrientationAuto:
        attribute = static_cast<Qt::WidgetAttribute>(130);
        break;
#else // QT_VERSION < 0x040702
    case ScreenOrientationLockPortrait:
        attribute = Qt::WA_LockPortraitOrientation;
        break;
    case ScreenOrientationLockLandscape:
        attribute = Qt::WA_LockLandscapeOrientation;
        break;
    default:
    case ScreenOrientationAuto:
        attribute = Qt::WA_AutoOrientation;
        break;
#endif // QT_VERSION < 0x040702
    };
    setAttribute(attribute, true);
}

void MainWindow::showExpanded()
{
#if defined(Q_OS_SYMBIAN) || defined(Q_WS_SIMULATOR)
    showFullScreen();
#elif defined(Q_WS_MAEMO_5)
    showMaximized();
#else
    show();
#endif
}
