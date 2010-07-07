#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtGui/QSplitter>
#include <QtGui/QTabWidget>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //QSplitter *splitter = new QSplitter(Qt::Horizontal,ui->widget);
    //QTabWidget *tabW_1 = new QTabWidget;
    //QTabWidget *tabW_2 = new QTabWidget;
    //splitter->addWidget(tabW_1);
    //splitter->addWidget(tabW_2);
    //splitter->setMaximumWidth(400);
    //splitter->setMinimumHeight(300);
    //splitter->show();

}

void MainWindow::setSplash(QSplashScreen * spl)
{
    ui->OgreWidget->setSplash(spl);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_dockProperties_destroyed()
{

}
