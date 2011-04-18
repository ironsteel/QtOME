#include "NewMaterialDialog.h"
#include "ui_NewMaterialDialog.h"
#include "MaterialManager.hpp"

NewMaterialDialog::NewMaterialDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewMaterialDialog)
{
    ui->setupUi(this);
    ui->createButton->setEnabled(false);
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
    QString workDir = MaterialManager::getSingletonPtr()->getWorkDir();

}

void NewMaterialDialog::activateOkButton(QString text)
{
    if(text.isEmpty())
        ui->createButton->setEnabled(false);
    else
        ui->createButton->setEnabled(true);
}
