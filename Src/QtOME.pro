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
    MaterialManager.cpp \
    TextEdit.cpp \
    Lexers/OgreMaterialLexer.cpp \
    CgEdit.cpp \
    Lexers/CgLexer.cpp

HEADERS  += mainwindow.h \
    TestWidget.h \
    QOgreWidget.h \
    SdkCameraMan.h \
    MaterialManager.hpp \
    TextEdit.h \
    Lexers/OgreMaterialLexer.h \
    CgEdit.h \
    Lexers/CgLexer.h

FORMS    += mainwindow.ui

LIBS += -lOgreMain\
        -lqscintilla2

RESOURCES += \
    QtOME.qrc
