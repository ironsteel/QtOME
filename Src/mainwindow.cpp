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
    connect(ui->workspaceTree, SIGNAL(itemDoubleClicked(QTreeWidgetItem*,int)),
            this, SLOT(workspaceItemSelected(QTreeWidgetItem*)));


    currMatName = "DefaultSettings";
    ui->workspaceTree->setColumnCount(1);
    ui->workspaceTree->setHeaderLabel("Materials");

    ui->wFP->setWindowTitle("Fragment Shader Editor");
    ui->wVP->setWindowTitle("Vertex Shader Editor");
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
    ui->logPanel->clear();
    Ogre::GpuProgramPtr vProgram;
    Ogre::GpuProgramPtr fProgram;
    if (!ui->VP->getShaderName().isEmpty()) {
         vProgram =
                Ogre::GpuProgramManager::getSingleton().getByName(ui->VP->getShaderName().toStdString());
        Ogre::LogManager::getSingleton().logMessage(vProgram->getName());
        vProgram->setSource(ui->VP->text().toStdString());
        vProgram->reload();
    }

    if (!ui->FP->getShaderName().isEmpty()) {
        fProgram =
                Ogre::GpuProgramManager::getSingleton().getByName(ui->FP->getShaderName().toStdString());
        fProgram->setSource(ui->FP->text().toStdString());
        fProgram->reload();
    }

    QString mat = this->removeWhiteSpaceCharacters();

    if (mat.isEmpty()) {
        return ;
    }

    ui->OgreWidget->setMaterial(mat.toStdString(), currMatName.toStdString());
}


QString MainWindow::removeWhiteSpaceCharacters()
{
    QString materialSource = this->ui->textEdit->text();

    // Split the source into separate lines
    QStringList materialSplited = materialSource.split(QRegExp("\n"), QString::SkipEmptyParts);

    for (int lineNumber = 0; lineNumber < materialSplited.size(); ++lineNumber)
    {
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
    MyLogListener *listener = ui->OgreWidget->mLogListener;
    Ogre::LogMessageLevel level = listener->getLogMessageLevel();
    QString msg = listener->getLogMsg();
    ui->logPanel->appendLogMessage(msg, level);

}

void MainWindow::newProject()
{
    QString Path = QFileDialog::getExistingDirectory(this);
    Ogre::LogManager::getSingleton().logMessage(Path.toStdString());

    if(Path.isEmpty())
        return ;

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
    for(int count = 0; count < itemNames.size(); ++count)
    {
        QTreeWidgetItem *matItem = new QTreeWidgetItem(ui->workspaceTree);
        QString parentName = itemNames.at(count);
        matItem->setText(0, parentName);
        matItem->setText(1, "material");
        Ogre::MaterialPtr parMat = Ogre::MaterialManager::getSingleton().getByName(parentName.toStdString());

        unsigned short numTech = parMat.getPointer()->getNumTechniques();

        for (int countTech = 0; countTech < numTech; ++countTech)
        {
            Ogre::Technique *parTech = parMat.getPointer()->getTechnique(countTech);
            int numPass = parTech->getNumPasses();
            QTreeWidgetItem *techItem = new QTreeWidgetItem(matItem);
            techItem->setText(0, QString("technique(")+QString(Ogre::String(parTech->getName()).c_str())+QString(")"));

            for (int countPass = 0; countPass < numPass; ++countPass)
            {
                QTreeWidgetItem *passItem = new QTreeWidgetItem(techItem);
                Ogre::Pass* pass = parTech->getPass(countPass);
                passItem->setText(0, QString("pass(")+QString(Ogre::String(pass->getName()).c_str())+QString(")"));
                passItem->setText(1, QString("pass"));

                if(pass->hasVertexProgram())
                {
                    QTreeWidgetItem *vpItem = new QTreeWidgetItem(passItem);
                    vpItem->setText(0,Ogre::String(pass->getVertexProgramName()).c_str());
                    vpItem->setText(1,QString("VertexProgram"));
                    vpItem->setText(2,QString(parentName));
                    vpItem->setText(3,QString(countTech));
                    vpItem->setText(4,QString(countPass));
                }
                if(pass->hasFragmentProgram())
                {
                    QTreeWidgetItem *fpItem = new QTreeWidgetItem(passItem);
                    fpItem->setText(0,Ogre::String(pass->getFragmentProgramName()).c_str());
                    fpItem->setText(1,QString("FragmentProgram"));
                    fpItem->setText(2,QString(parentName));
                    fpItem->setText(3,QString(countTech));
                    fpItem->setText(4,QString(countPass));
                }
                if(pass->hasGeometryProgram())
                {
                    QTreeWidgetItem *gpItem = new QTreeWidgetItem(passItem);
                    gpItem->setText(0,Ogre::String(pass->getGeometryProgramName()).c_str());
                }
            }
        }
    }
}

void MainWindow::workspaceItemSelected(QTreeWidgetItem* Item)
{
    QString itemType = Item->text(1);

    if(itemType == "material")
    {
        QString itemName = Item->text(0);
        Ogre::LogManager::getSingleton().logMessage(itemName.toStdString());

        QString materialItemFileName = ui->OgreWidget->manager->getFileName(itemName);
        Ogre::LogManager::getSingleton().logMessage(materialItemFileName.toStdString());
        ui->textEdit->openFile(materialItemFileName, itemName);
        currMatName = itemName;
        ui->subwindow_2->setWindowTitle("Material Script: " + materialItemFileName.section('/', -1));

        /* Clear the shader source editors
         * when switching to a different material */
        ui->VP->clearData();
        ui->FP->clearData();
    }
    if(itemType == "VertexProgram" && Item->text(2)==currMatName)
    {
        Ogre::MaterialPtr Mat = Ogre::MaterialManager::getSingleton().getByName(currMatName.toStdString());
        int numTech = Item->text(3).toInt();
        int numPass = Item->text(4).toInt();
        Ogre::Pass* pass = Mat->getTechnique(numTech)->getPass(numPass);
        QString f = ui->OgreWidget->manager->getWorkDir() + pass->getVertexProgram()->getSourceFile().c_str();
        Ogre::LogManager::getSingleton().logMessage(f.toStdString());
        ui->VP->openFile(f);
        ui->VP->setShaderName(Item->text(0));
    }
    if(itemType == "FragmentProgram" && Item->text(2)==currMatName)
    {
        Ogre::MaterialPtr Mat = Ogre::MaterialManager::getSingleton().getByName(currMatName.toStdString());
        int numTech = Item->text(3).toInt();
        int numPass = Item->text(4).toInt();
        Ogre::Pass* pass = Mat->getTechnique(numTech)->getPass(numPass);
        QString f = ui->OgreWidget->manager->getWorkDir() + pass->getFragmentProgram()->getSourceFile().c_str();
        Ogre::LogManager::getSingleton().logMessage(f.toStdString());
        ui->FP->openFile(f);
        ui->FP->setShaderName(Item->text(0));
    }

    Ogre::LogManager::getSingleton().logMessage(itemType.toStdString());
}

void MainWindow::saveAll()
{
    ui->textEdit->saveFile();
    ui->VP->saveFile();
    ui->FP->saveFile();
}
