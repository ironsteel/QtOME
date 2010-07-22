#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtGui/QSplitter>
#include <QtGui/QTabWidget>
#include <QFileDialog>
#include <QMessageBox>
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

    QString fullFilePath = QFileDialog::getOpenFileName(this,
       tr("Open Material Script"), "./", tr("Material scripts (*.material )"));

    if ( fullFilePath.isEmpty() ) { // If no file is loaded
        QMessageBox::warning(this, tr("QtOME"), tr("No file selected!"));
        return ;
    }

    QString fileName = fullFilePath.section('/', -1);

    ui->matEditor->openFile(fullFilePath);
    this->ui->subwindow->setWindowTitle(fileName);

    //QStringList places = fullFilePath.split("/");
    //places.pop_back();
    //QString pathOnly = places.join("/");

    //Ogre::ResourceGroupManager::getSingleton().addResourceLocation( pathOnly.toStdString() ,"FileSystem","ImportedMaterials");
    //Ogre::ResourceGroupManager::getSingleton().initialiseResourceGroup("ImportedMaterials");

    ui->listWidget->clear();
    QStringList materials = ui->OgreWidget->manager->getMaterialList();
    ui->listWidget->addItems(materials);

}

void MainWindow::importMesh()
{

    QString s = QFileDialog::getOpenFileName(this,
       tr("Import *.mesh file"), "./", tr("Meshes (*.mesh )"));

    if(s.isEmpty()) { // If no file is loaded
        return ;
    }

    s=ui->OgreWidget->changeMesh(s);
    this->setWindowTitle(s);
}

void MainWindow::saveMatScript()
{
    this->ui->matEditor->saveFile();
}

void MainWindow::applyMaterial()
{
    ui->OgreWidget->clearMaterial();
    QString mat = this->ui->matEditor->toPlainText();
    ui->OgreWidget->setMaterial(mat.toStdString());
}
