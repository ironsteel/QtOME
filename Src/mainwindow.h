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

    // Remove white space characters from empty new lines
    // This is done becouse Ogre hangs if the material script
    // has new line with whitespace characters only
    QString removeWhiteSpaceCharacters();

private slots:
    void loadFile();
    void saveMatScript();
    void importMesh();
    void applyMaterial();

    // This slot is used to write a message to the logPanel
    void writeToLogPanel();
};

#endif // MAINWINDOW_H
