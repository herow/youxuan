#include "fangtang.h"
#include "ui_fangtang.h"
#include "qsqlquerymodel.h"
#include <QModelIndex>
fangtang::fangtang(QSqlQueryModel *model,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::fangtang)
{
    ui->setupUi(this);
    ui->tableViewCaption->setModel(model); // model先自己创建

      // table view双击后打开对话框
    connect(ui->tableViewCaption, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(showDetail(QModelIndex)));
}

fangtang::~fangtang()
{
    delete ui;
}
void fangtang::showDetail(QModelIndex index) {
    ui->textEdit->setText(index.model()->data(index, Qt::EditRole).toString());
}
