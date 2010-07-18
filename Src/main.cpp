#include <QtGui/QApplication>
#include "mainwindow.h"
#include <Qt/qsyntaxhighlighter.h>
#include <QtGui/QSplashScreen>
#include <QtGui/QToolBar>
#include <QtGui/QPushButton>

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    Q_INIT_RESOURCE(QtOME);
    MainWindow w;

    QSplashScreen *splash = new QSplashScreen;
    splash->setPixmap(QPixmap(":/splash"));

    Qt::Alignment topRight = Qt::AlignRight | Qt::AlignTop;
    splash->show();splash->showMessage(QObject::tr("Setting up the main window..."), topRight, Qt::black);

    w.setSplash(splash);

    //QObject::connect(w.action_Quit, SIGNAL(triggered()), MainWindow, SLOT(close()));
    w.showMaximized();

    return a.exec();
}
