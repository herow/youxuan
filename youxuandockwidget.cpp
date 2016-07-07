#include "youxuandockwidget.h"
#include "ui_youxuandockwidget.h"

YouXuanDockWidget::YouXuanDockWidget(QWidget *parent) :
    QDockWidget(parent),
    ui(new Ui::YouXuanDockWidget)
{
    ui->setupUi(this);
}

YouXuanDockWidget::~YouXuanDockWidget()
{
    delete ui;
}
