#include "NewMaterialDialog.h"
#include "ui_NewMaterialDialog.h"

NewMaterialDialog::NewMaterialDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewMaterialDialog)
{
    ui->setupUi(this);
}

NewMaterialDialog::~NewMaterialDialog()
{
    delete ui;
}
