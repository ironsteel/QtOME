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
                                  const Ogre::String &logName, bool &)
{

    logMesg = QString(message.c_str());
    this->messageLevel = lml;
    Q_UNUSED(maskDebug);
    Q_UNUSED(logName);

    emit logMessageUpdated();
}

QString MyLogListener::getLogMsg()
{
    return logMesg;
}

Ogre::LogMessageLevel MyLogListener::getLogMessageLevel()
{
    return messageLevel;
}
