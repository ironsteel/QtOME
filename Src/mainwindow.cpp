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

    ui->logPanel->setReadOnly(true);
    ui->logPanel->setFont(QFont("Monospace", 8, 2));

    connect(ui->OgreWidget->mLogListener, SIGNAL(logMessageUpdated()),
            this, SLOT(writeToLogPanel()));
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
        return ;
    }

    QString fileName = fullFilePath.section('/', -1);


    ui->textEdit->openFile(fullFilePath);
    this->ui->subwindow_2->setWindowTitle("Material Editor: " + fileName);

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
    this->ui->textEdit->saveFile();
}

void MainWindow::applyMaterial()
{

    QString mat = this->removeWhiteSpaceCharacters();

    if (mat.isEmpty() == true) {
        return ;
    }

    ui->OgreWidget->clearMaterial();
    ui->OgreWidget->setMaterial(mat.toStdString());

}


QString MainWindow::removeWhiteSpaceCharacters()
{
    QString materialSource = this->ui->textEdit->text();

    // Split the source into separate lines
    QStringList materialSplited = materialSource.split(QRegExp("\n"), QString::SkipEmptyParts);

    for (int lineNumber = 0; lineNumber < materialSplited.size(); ++lineNumber) {

        QString line = materialSplited.at(lineNumber);

        // Remove whitespace characters from the current line
        QString trimmedLine = line.trimmed();

        if (trimmedLine.isEmpty() == true) {
            // This replaces the line with whitespace characters
            // with an empty line
            materialSplited.replace(lineNumber, trimmedLine);
        }
    }

    return materialSplited.join("\n");

}

void MainWindow::writeToLogPanel()
{
    ui->logPanel->appendPlainText(ui->OgreWidget->mLogListener->getLogMsg());
}
