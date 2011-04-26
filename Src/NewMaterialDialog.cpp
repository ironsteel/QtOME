#include "NewMaterialDialog.h"
#include "ui_NewMaterialDialog.h"
#include "MaterialManager.hpp"
#include <QFile>
#include <QTextStream>

NewMaterialDialog::NewMaterialDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewMaterialDialog)
{
    ui->setupUi(this);
    ui->createButton->setEnabled(false);
    ui->label_3->setEnabled(false);
    ui->fragmentShaderName->setEnabled(false);
    ui->label_2->setEnabled(false);
    ui->vertexShaderName->setEnabled(false);
}

void NewMaterialDialog::processDialog()
{

    QString tempName = ui->materialName->text();
    if(!tempName.isEmpty()) {
        this->materialName = tempName;
    }
}

NewMaterialDialog::~NewMaterialDialog()
{
    delete ui;
}

void NewMaterialDialog::accept()
{
    MaterialManager* matMgr = MaterialManager::getSingletonPtr();
    QString workDir = matMgr->getWorkDir();
    if( !workDir.isEmpty() && matMgr->getFileName(ui->materialName->text())=="" )
    {
        QFile matFile(workDir + ui->materialName->text() + ".material");
        if (!matFile.open(QIODevice::WriteOnly | QIODevice::Text))
                 return;
        QTextStream file(&matFile);
        file << "material " << ui->materialName->text() << "\n{\n\t\n}";
        matFile.close();
        this->close();
    }
    else if (workDir.isEmpty()) {
        Ogre::LogManager::getSingleton().logMessage("Workspace not set!");
    }
    else if (matMgr->getFileName(ui->materialName->text())!="") {
        Ogre::LogManager::getSingleton().logMessage("Material exists!");
    }
}

void NewMaterialDialog::activateOkButton(QString text)
{
    ui->createButton->setEnabled(!text.isEmpty());
}
void NewMaterialDialog::activateFragmet(bool enabled)
{
    ui->label_3->setEnabled(enabled);
    ui->fragmentShaderName->setEnabled(enabled);
}
void NewMaterialDialog::activateVertex(bool enabled)
{
    ui->label_2->setEnabled(enabled);
    ui->vertexShaderName->setEnabled(enabled);
}
