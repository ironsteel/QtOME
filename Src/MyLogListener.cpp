#include "MyLogListener.h"

MyLogListener::MyLogListener(QWidget *parent)
    : QWidget(parent), Ogre::LogListener()
{
}

MyLogListener::~MyLogListener()
{
}

void MyLogListener::messageLogged(const Ogre::String &message,
                                  Ogre::LogMessageLevel lml,
                                  bool maskDebug,
                                  const Ogre::String &logName)
{
    logMesg = QString(message.c_str());
    Q_UNUSED(lml);
    Q_UNUSED(maskDebug);
    Q_UNUSED(logName);

    emit logMessageUpdated();
}

QString MyLogListener::getLogMsg()
{
    return logMesg;
}
