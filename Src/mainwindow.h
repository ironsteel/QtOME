#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtGui/QSplashScreen>
#include <QListWidgetItem>
#include <QTreeWidgetItem>
#include <OGRE/Ogre.h>

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
    void populateWorkSpaceTree(const QStringList &itemNames);


private:
    void keyPressEvent(QKeyEvent* e);
    void keyReleaseEvent(QKeyEvent* e);

    // Remove white space characters from empty new lines
    // This is done becouse Ogre hangs if the material script
    // has new line with whitespace characters only
    QString removeWhiteSpaceCharacters();

    QString     currMatName;

private slots:
    void loadFile();
    void saveMatScript();
    void importMesh();
    void applyMaterial();
    void newProject();
    void materialSelected();
    void setCurrentMatName(QListWidgetItem* item);
    void workspaceItemSelected(QTreeWidgetItem* Item);

    // This slot is used to write a message to the logPanel
    void writeToLogPanel();
};

#endif // MAINWINDOW_H
