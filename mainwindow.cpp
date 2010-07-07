#include "mainwindow.h"
#include "CodeEditor.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
  editor = new CodeEditor; // Create a texteditor
  setCentralWidget(editor);
  resize(600, 400);

  setWindowTitle(tr("CodeEditor"));

}

MainWindow::~MainWindow()
{

}


