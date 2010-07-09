#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtGui/QSplitter>
#include <QtGui/QTabWidget>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->matEditor->setupCurrentCompleter(":/Build/Data/wordlist.txt");

}

void MainWindow::setSplash(QSplashScreen * spl)
{
    ui->OgreWidget->setSplash(spl);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_dockProperties_destroyed()
{

}

void MainWindow::loadFile()
{
    ui->matEditor->setFile(QFileDialog::getOpenFileName(this,
          tr("Open Material Script"), "./", tr("Material scripts (*.material )")));
}
