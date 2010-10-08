#include "WorkspaceWidget.hpp"
#include <OGRE/Ogre.h>

WorkspaceWidget::WorkspaceWidget(QWidget *parent) :
    QTreeWidget(parent)
{
}
/*
void WorkspaceWidget::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::RightButton)
        Ogre::LogManager::getSingleton().logMessage("Right mouse button pressed on WorkspaceWidget");
}
*/
