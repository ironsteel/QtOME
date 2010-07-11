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
private:
    void keyPressEvent(QKeyEvent* e);
    void keyReleaseEvent(QKeyEvent* e);

private slots:
    void loadFile();
    void importMesh();
};

#endif // MAINWINDOW_H
