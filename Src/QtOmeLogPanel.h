#ifndef QTOMELOGPANEL_H
#define QTOMELOGPANEL_H
#include <QTextEdit>
#include <OGRE/OgreLogManager.h>
class QtOmeLogPanel : public QTextEdit
{
public:
    QtOmeLogPanel(QWidget *parent);
    void appendLogMessage(QString logMsg, Ogre::LogMessageLevel logLevel);
};

#endif // QTOMELOGPANEL_H
