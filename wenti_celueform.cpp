#include <QCloseEvent>
#include "wenti_celueform.h"
#include "ui_wenti_celueform.h"
#include "horizontal_proxy_model.h"
#include "qdatawidgetmapper.h"
#include "qsqltablemodel.h"
WenTi_CeLueForm::WenTi_CeLueForm(QSqlQueryModel *model,QSqlTableModel *modelPro_Strategy,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WenTi_CeLueForm)
{
    ui->setupUi(this);
    Horizontal_proxy_model* proxy_model = new Horizontal_proxy_model();
    proxy_model->setSourceModel((QAbstractItemModel *)model);
    ui->tableView->setModel(proxy_model);

    mapper = new QDataWidgetMapper(this);
    mapper->setSubmitPolicy(QDataWidgetMapper::AutoSubmit);
    mapper->setModel((QAbstractItemModel *)modelPro_Strategy);

    mapper->addMapping(ui->textEditProblem, 2);
    mapper->addMapping(ui->textEditStrategy, 3);


    mapper->toFirst();

}

WenTi_CeLueForm::~WenTi_CeLueForm()
{
    delete ui;
    delete mapper;
}
void WenTi_CeLueForm::closeEvent(QCloseEvent *event)
{
    mapper->submit();
    event->accept();
}
