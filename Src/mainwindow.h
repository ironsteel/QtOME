#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtGui/QSplashScreen>

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public:
    void setSplash(QSplashScreen * spl);
    Ui::MainWindow *ui;

private slots:

    void on_dockProperties_destroyed();
};

#endif // MAINWINDOW_H
