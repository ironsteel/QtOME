#include <QtGui/QApplication>
#include "mainwindow.h"
#include <Qt/qsyntaxhighlighter.h>
#include <QtGui/QSplashScreen>
#include <QtGui/QToolBar>
#include <QtGui/QPushButton>

int main(int argc, char *argv[])
{

    Q_INIT_RESOURCE(QtOME);
    QApplication a(argc, argv);
    MainWindow w;

    QSplashScreen *splash = new QSplashScreen;
    splash->setPixmap(QPixmap("Data/splash.png"));

    Qt::Alignment topRight = Qt::AlignRight | Qt::AlignTop;
    splash->show();splash->showMessage(QObject::tr("Setting up the main window..."), topRight, Qt::black);

    w.setSplash(splash);

    //QObject::connect(w.action_Quit, SIGNAL(triggered()), MainWindow, SLOT(close()));
    w.showMaximized();

    return a.exec();
}
