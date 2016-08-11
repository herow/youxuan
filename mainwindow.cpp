#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "youxuandockwidget.h"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect( ui->youxuanaction, SIGNAL(triggered()), this, SLOT( showWizard() ) );

}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::showWizard()
{
    YouXuanDockWidget * wizard = new YouXuanDockWidget();
    wizard->show();
}
