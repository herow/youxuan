#include "wenti_celueform.h"
#include "ui_wenti_celueform.h"
#include "horizontal_proxy_model.h"
WenTi_CeLueForm::WenTi_CeLueForm(QSqlQueryModel *model,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WenTi_CeLueForm)
{
    ui->setupUi(this);
    Horizontal_proxy_model* proxy_model = new Horizontal_proxy_model();
    proxy_model->setSourceModel((QAbstractItemModel *)model);
    ui->tableView->setModel(proxy_model);
}

WenTi_CeLueForm::~WenTi_CeLueForm()
{
    delete ui;
}
