#ifndef MYLOGLISTENER_H
#define MYLOGLISTENER_H
#include <OGRE/OgreLogManager.h>
#include <QString>
#include <QWidget>



class MyLogListener :  public QWidget, public Ogre::LogListener
{
    Q_OBJECT

public:
    MyLogListener(QWidget *parent);
    ~MyLogListener();
public:
   // This is method called every time
   // when a log message is passed to Ogre
   virtual void messageLogged(const Ogre::String &message,
                               Ogre::LogMessageLevel lml,
                               bool maskDebug,
                               const Ogre::String &logName);
signals:
   // This signal is emited when
   // a new log message is created
   void logMessageUpdated();
public:
    QString getLogMsg();
private:
    QString logMesg;
};

#endif // MYLOGLISTENER_H
