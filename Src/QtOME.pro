#-------------------------------------------------
#
# Project created by QtCreator 2010-07-02T21:23:54
#
#-------------------------------------------------

QT       += core gui

TARGET = ../Build/QtOME
TEMPLATE = app

OBJECTS_DIR=../QtOME-Objects
MOC_DIR =../QtOME-Objects
UI_DIR=../QtOME-Objects

SOURCES += main.cpp\
        mainwindow.cpp \
    TestWidget.cpp \
    QOgreWidget.cpp \
    Highlighter.cpp \
    CodeEditor.cpp \
    MaterialManager.cpp

HEADERS  += mainwindow.h \
    TestWidget.h \
    QOgreWidget.h \
    Highlighter.h \
    CodeEditor.h \
    SdkCameraMan.h \
    MaterialManager.hpp

FORMS    += mainwindow.ui

LIBS += -lOgreMain

RESOURCES += \
    QtOME.qrc
