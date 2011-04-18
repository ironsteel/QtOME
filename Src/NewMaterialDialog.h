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
    void processDialog();

    ~NewMaterialDialog();
public slots:
    void accept();
    void activateOkButton(QString text);

private:
    Ui::NewMaterialDialog *ui;
    QString materialName;
    QString vertexShaderName;
    QString fragmentShaderName;
};

#endif // NEWMATERIALDIALOG_H
