#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtGui/QSplitter>
#include <QtGui/QTabWidget>
#include <QFileDialog>
#include <QMessageBox>
#include <QTreeWidgetItem>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->logPanel->setReadOnly(true);
    ui->logPanel->setFont(QFont("Monospace", 8, 2));

    connect(ui->OgreWidget->mLogListener, SIGNAL(logMessageUpdated()),
            this, SLOT(writeToLogPanel()));
    connect(ui->listWidget, SIGNAL(doubleClicked(QModelIndex)), this , SLOT(materialSelected()));
    connect(ui->workspaceTree, SIGNAL(itemClicked(QTreeWidgetItem*,int)),
            this, SLOT(workspaceItemSelected()));
    currMatName = "DefaultSettings";
    ui->workspaceTree->setColumnCount(1);
    ui->workspaceTree->setHeaderLabel("Materials");



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

    QStringList places = fullFilePath.split("/");
    places.pop_back();
    QString pathOnly = places.join("/");

    Ogre::ResourceGroupManager::getSingleton().addResourceLocation( pathOnly.toStdString() ,"FileSystem","mm");
    Ogre::ResourceGroupManager::getSingleton().initialiseResourceGroup("mm");

    ui->listWidget->clear();
   // QStringList materials = ui->OgreWidget->manager->getMaterialList();
    //ui->listWidget->addItems(materials);

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

    ui->OgreWidget->setMaterial(mat.toStdString(), currMatName.toStdString());
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

void MainWindow::newProject()
{
    QString Path = QFileDialog::getExistingDirectory(this);
    Ogre::LogManager::getSingleton().logMessage(Path.toStdString());

    ui->listWidget->clear();
    QStringList materials = ui->OgreWidget->manager->getMaterialList(Path);
    ui->listWidget->addItems(materials);

    this->populateWorkSpaceTree(materials);





}

void MainWindow::materialSelected()
{
    QString matName = ui->listWidget->currentItem()->text();

   QString matFileName = ui->OgreWidget->manager->getFileName(matName);

   Ogre::LogManager::getSingleton().logMessage(matFileName.toStdString());

   ui->textEdit->openFile(matFileName);
}

void MainWindow::setCurrentMatName(QListWidgetItem *item)
{
    currMatName = item->text();

}

void MainWindow::populateWorkSpaceTree(const QStringList &itemNames)
{
    for(int count = 0; count < itemNames.size(); ++count) {
        QTreeWidgetItem *matItem = new QTreeWidgetItem(ui->workspaceTree);
        QString parentName = itemNames.at(count);
        matItem->setText(0, parentName);
        matItem->setText(1, "material");
        Ogre::MaterialPtr parMat = Ogre::MaterialManager::getSingleton().getByName(parentName.toStdString());

        unsigned short numTech = parMat.getPointer()->getNumTechniques();

        for (int countTech = 0; countTech < numTech; ++countTech) {
            Ogre::Technique *parTech = parMat.getPointer()->getTechnique(countTech);
            int numPass = parTech->getNumPasses();
            QTreeWidgetItem *techItem = new QTreeWidgetItem(matItem);
            techItem->setText(0, "technique");

            for (int countPass = 0; countPass < numPass; ++countPass) {
                QTreeWidgetItem *passItem = new QTreeWidgetItem(techItem);
                passItem->setText(0, "pass");
            }
        }
    }
}

void MainWindow::workspaceItemSelected()
{
    QTreeWidgetItem *selection = ui->workspaceTree->currentItem();

    QString itemType = selection->text(1);
    if (itemType == "material") {
        QString itemName = selection->text(0);
        Ogre::LogManager::getSingleton().logMessage(itemName.toStdString());

        QString materialItemFileName = ui->OgreWidget->manager->getFileName(itemName);
        Ogre::LogManager::getSingleton().logMessage(materialItemFileName.toStdString());
        ui->textEdit->openFile(materialItemFileName);
        currMatName = itemName;

    }

    Ogre::LogManager::getSingleton().logMessage(itemType.toStdString());
}
