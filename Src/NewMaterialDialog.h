#ifndef NEWMATERIALDIALOG_H
#define NEWMATERIALDIALOG_H

#include <QDialog>

namespace Ui {
    class NewMaterialDialog;
}

class NewMaterialDialog : public QDialog
{
    Q_OBJECT

public:
    explicit NewMaterialDialog(QWidget *parent = 0);
    ~NewMaterialDialog();

private:
    Ui::NewMaterialDialog *ui;
};

#endif // NEWMATERIALDIALOG_H
