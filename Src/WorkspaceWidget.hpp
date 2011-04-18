#ifndef WORKSPACEWIDGET_HPP
#define WORKSPACEWIDGET_HPP



#include <QTreeWidget>
#include <QMouseEvent>
#include "NewMaterialDialog.h"
#include "MaterialManager.hpp"



class WorkspaceWidget : public QTreeWidget
{
    Q_OBJECT
public:
    explicit WorkspaceWidget(QWidget *parent = 0);
    void     mousePressEvent ( QMouseEvent * event );


signals:

public slots:
    void     showDialog();
private:
    QAction *actionNewMaterial;

};

#endif // WORKSPACEWIDGET_HPP
