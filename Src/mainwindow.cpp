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

void MainWindow::keyPressEvent(QKeyEvent * e)
{
    if(e->key() == Qt::Key_Shift)
        ui->OgreWidget->sdkCam->setShift(true);
}

void MainWindow::keyReleaseEvent(QKeyEvent* e)
{
    if(e->key() == Qt::Key_Shift)
        ui->OgreWidget->sdkCam->setShift(false);
}

void MainWindow::loadFile()
{
    QString s = QFileDialog::getOpenFileName(this,
       tr("Open Material Script"), "./", tr("Material scripts (*.material )"));
    ui->matEditor->setFile(s);
    this->setWindowTitle(s);
}

void MainWindow::importMesh()
{
    QString s = QFileDialog::getOpenFileName(this,
       tr("Import *.mesh file"), "./", tr("Meshes (*.mesh )"));
    s=ui->OgreWidget->changeMesh(s);
    this->setWindowTitle(s);
}
