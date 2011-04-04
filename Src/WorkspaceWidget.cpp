#include "WorkspaceWidget.hpp"
#include "QMenu"
#include <OGRE/Ogre.h>

WorkspaceWidget::WorkspaceWidget(QWidget *parent) :
    QTreeWidget(parent)
{
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
        contextMenu->addAction("New Action");
        contextMenu->popup(QWidget::mapToGlobal(cursorPos));
        return;
    }
    QTreeWidget::mousePressEvent(event);

}

