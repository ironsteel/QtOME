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
   QString fullFilePath = QFileDialog::getOpenFileName(this,
       tr("Open Material Script"), "./", tr("Material scripts (*.material )"));

   QString fileName = fullFilePath.section('/', -1);

    ui->matEditor->openFile(fullFilePath);
    this->ui->subwindow->setWindowTitle(fileName);

    //QStringList places = fullFilePath.split("/");
    //places.pop_back();
    //QString pathOnly = places.join("/");

    //Ogre::ResourceGroupManager::getSingleton().addResourceLocation( pathOnly.toStdString() ,"FileSystem","ImportedMaterials");
    //Ogre::ResourceGroupManager::getSingleton().initialiseResourceGroup("ImportedMaterials");

    //ui->listWidget->clear();
    //QStringList materials = ui->OgreWidget->manager->getMaterialList();
    //ui->listWidget->addItems(materials);

}

void MainWindow::importMesh()
{
    QString s = QFileDialog::getOpenFileName(this,
       tr("Import *.mesh file"), "./", tr("Meshes (*.mesh )"));
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
    Ogre::String script = mat.toStdString();
    Ogre::MemoryDataStream *memoryStream = new Ogre::MemoryDataStream((void*)script.c_str(), script.length() * sizeof(char));
    Ogre::DataStreamPtr dataStream(memoryStream);
    Ogre::MaterialManager::getSingleton().parseScript(dataStream, Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
    Ogre::StringVector lines = Ogre::StringUtil::split(script, "\n");
    for(Ogre::StringVector::iterator line = lines.begin(); line != lines.end(); line++)
    {
        Ogre::StringVector params = Ogre::StringUtil::split(*line, " \t:");
        if (params[0] == "material")
        {
            Ogre::String materialName = params[1];
            Ogre::MaterialPtr material = Ogre::MaterialManager::getSingleton().getByName(materialName, Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
            material->compile();
            ui->OgreWidget->setMaterial(&material);
        }
    }

}
