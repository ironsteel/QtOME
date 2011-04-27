#include "QtOmeLogPanel.h"

QtOmeLogPanel::QtOmeLogPanel(QWidget *parent)
    :QTextEdit(parent)
{
    this->setFont(QFont("Monospace", 8, 2));
    setTextColor(QColor("black"));
}

void QtOmeLogPanel::appendLogMessage(QString logMsg, Ogre::LogMessageLevel logLevel)
{
    if(logLevel == Ogre::LML_NORMAL || logLevel == Ogre::LML_TRIVIAL) {

        if(logMsg.indexOf("WARNING") != -1 || logMsg.indexOf("Compiler error") != -1) {
            setTextColor(QColor("red"));
            append(logMsg);
            return;
        }

        setTextColor(QColor("black"));
        append(logMsg);
        return;
    } else if (logLevel == Ogre::LML_CRITICAL) {
        setTextColor(QColor("red"));
        append(logMsg);
        return;
    }

}
