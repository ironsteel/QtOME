#include "WorkspaceWidget.hpp"
#include "QMenu"
#include <OGRE/Ogre.h>

WorkspaceWidget::WorkspaceWidget(QWidget *parent) :
    QTreeWidget(parent)
{
    this->actionNewMaterial = new QAction("New Material", this);
    connect(actionNewMaterial,SIGNAL(triggered()),
            this, SLOT(showDialog()));
}

void WorkspaceWidget::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::RightButton) {
        Ogre::LogManager::getSingleton().logMessage("Right mouse button clicked.");
        QPoint cursorPos = event->pos();

        QTreeWidgetItem *selItem = this->itemAt(cursorPos);
        if(selItem) {
            QString itemType = selItem->text(1);
            Ogre::LogManager::getSingleton().logMessage("Item type: " + itemType.toStdString());
        }
        QMenu *contextMenu = new QMenu(this);

        contextMenu->addAction(actionNewMaterial);
        contextMenu->popup(QWidget::mapToGlobal(cursorPos));
        return;
    }
    QTreeWidget::mousePressEvent(event);

}

void WorkspaceWidget::showDialog()
{
    NewMaterialDialog *newMaterial = new NewMaterialDialog(this);
    newMaterial->show();
    MaterialManager *matMgr = MaterialManager::getSingletonPtr();
    Ogre::LogManager::getSingleton().logMessage("Working dir: " + matMgr->getWorkDir().toStdString());

}
