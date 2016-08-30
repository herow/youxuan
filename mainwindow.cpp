#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "youxuandockwidget.h"
#include "connection.h"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect( ui->youxuanaction, SIGNAL(triggered()), this, SLOT( showWizard() ) );
    if (!createConnection())
        return  ;
     wizard = new YouXuanDockWidget();
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::showWizard()
{

    wizard->show();
}
