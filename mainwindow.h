#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include <QtGui/QMainWindow>
#include <QAbstractItemModel>
#include <QStringListModel>
#include "CodeEditor.h"
#include "Highlighter.h"
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    CodeEditor *editor; // TextEditor with completion feture added

};

#endif // MAINWINDOW_H
