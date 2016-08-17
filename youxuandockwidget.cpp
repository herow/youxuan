#include "youxuandockwidget.h"
#include "ui_youxuandockwidget.h"
#include "kongxinstatus.h"
#include "diaochaform.h"
#include "imagecollection.h"
#include "fangtang.h"
#include "teshustatusform.h"
#include "wenti_celueform.h"
#include "chubufanganform.h"
#include "cunminyijianform.h"
#include "zhengfuyaoqiuform.h"
#include "finalfanganform.h"
#include "connection.h"

#include "comboboxdelegate.h"
#include "horizontal_proxy_model.h"
#include "view.h"
#include <QSqlDatabase>
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QtSql>
#include <QtGui>

YouXuanDockWidget::YouXuanDockWidget(QWidget *parent) :
    QDockWidget(parent),
    ui(new Ui::YouXuanDockWidget)
{
    ui->setupUi(this);
    connect( ui->btnKongxinStatus, SIGNAL(clicked()), this, SLOT( show_kongxin_status() ) );

    connect( ui->btnSurveyForm, SIGNAL(clicked()), this, SLOT( show_surveyForm() ) );
    connect( ui->btnPictureCollet, SIGNAL(clicked()), this, SLOT( show_picturecollect() ) );
    connect( ui->btnSemiStructSurvey, SIGNAL(clicked()), this, SLOT( show_semisurvey() ) );

    connect( ui->btnSpecStatus, SIGNAL(clicked()), this, SLOT( show_specstatus() ) );

    connect( ui->btnProblemStrategy, SIGNAL(clicked()), this, SLOT( show_ProblemStrategy() ) );

    connect( ui->btnInitStrategy, SIGNAL(clicked()), this, SLOT( show_InitStrategy() ) );
    connect( ui->btnPublicOpinion, SIGNAL(clicked()), this, SLOT( show_PublicOpinion() ) );
    connect( ui->btnGovOpinion, SIGNAL(clicked()), this, SLOT( show_GovOpinion() ) );
    connect( ui->btnFinalSolution, SIGNAL(clicked()), this, SLOT( show_FinalSolution() ) );

    if (!createConnection())
        return  ;
    QSqlTableModel *model= new QSqlTableModel;
    model->setTable("test");
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model->select();

    mapper = new QDataWidgetMapper(this);
    mapper->setModel(model);
    mapper->setItemDelegate(new ComboBoxDelegate(this));
    mapper->addMapping(ui->comboxKongxc, model->fieldIndex("field3"));
    mapper->addMapping(ui->comboxZhengzhi, model->fieldIndex("field4"));
    mapper->addMapping(ui->lineEditZonghushu, model->fieldIndex("field5"));
    mapper->addMapping(ui->lineEditTongyi, model->fieldIndex("field6"));
    mapper->addMapping(ui->lineEditFandui, model->fieldIndex("field7"));
    mapper->addMapping(ui->comboxGaizaoyiyuan, model->fieldIndex("field8"));

    mapper->toFirst();



    QTableView *view = new QTableView;
    view->setModel(model);
    view->show();

}

YouXuanDockWidget::~YouXuanDockWidget()
{
    delete ui;
}

void YouXuanDockWidget::show_kongxin_status()
{
//     KongXinStatus * wid = new KongXinStatus(this);
//     wid->show();
    QSqlQueryModel *model= new QSqlTableModel;
    // Set character encoding to UTF8

    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
     QTextCodec *codec =QTextCodec::codecForName("UTF-8");
    const char * str = "空心化程度";
    const char * strCunname = "村名称";
    const char * strXiangname = "乡名称";
    QString tableName=codec->toUnicode(str);
    QString cunName=codec->toUnicode(strCunname);
    QString xiangName=codec->toUnicode(strXiangname);

     QString fullSql;
     fullSql = QString( "select * from '%1' where `%2`='%3' and `%4`='%5'" )
             .arg( tableName ).arg(cunName).arg(ui->comboBoxCunname->currentText())
             .arg(xiangName).arg(ui->comboBoxXiangname->currentText());
   // QMessageBox::information(NULL, "Title", fullSql, QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);

     model->setQuery(fullSql) ;//where id=101
//    model->setHeaderData(0, Qt::Horizontal, QObject::tr("乡名称"));
//    model->setHeaderData(1, Qt::Horizontal, QObject::tr("村名称"));
//    model->setHeaderData(2, Qt::Horizontal, QObject::tr("常住人口比重"));
//    model->setHeaderData(3, Qt::Horizontal, QObject::tr("废弃率"));
//    model->setHeaderData(4, Qt::Horizontal, QObject::tr("空置率"));
//    model->setHeaderData(4, Qt::Horizontal, QObject::tr("空废宗地聚集度"));
    Horizontal_proxy_model* proxy_model = new Horizontal_proxy_model();
    proxy_model->setSourceModel(model);

    QTableView *view = new QTableView;
    view->setModel(proxy_model);
    view->horizontalHeader()->hide();
    view->show();
}
void YouXuanDockWidget::show_surveyForm()
{
    QSqlQueryModel *model= new QSqlTableModel;
    // Set character encoding to UTF8

    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    QTextCodec *codec =QTextCodec::codecForName("UTF-8");
    const char * str = "调查问卷";
    const char * strCunname = "村名称";
    const char * strXiangname = "乡名称";
    QString tableName=codec->toUnicode(str);
    QString cunName=codec->toUnicode(strCunname);
    QString xiangName=codec->toUnicode(strXiangname);

    QString fullSql;
    fullSql = QString( "select * from '%1' where `%2`='%3' and `%4`='%5'" )
             .arg( tableName ).arg(cunName).arg(ui->comboBoxCunname->currentText())
             .arg(xiangName).arg(ui->comboBoxXiangname->currentText());
   // QMessageBox::information(NULL, "Title", fullSql, QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);

    model->setQuery(fullSql) ;//where id=101



    QTableView *view = new QTableView;
    view->setModel(model);
    //view->horizontalHeader()->hide();
    view->show();
}
void YouXuanDockWidget::show_picturecollect()
{
//     ImageCollection * wid = new ImageCollection();
//     wid->show();
     View *view=new View("offices", "images");
     QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
     QTextCodec *codec =QTextCodec::codecForName("UTF-8");
     const char * str = "数据图件收集";
     QString winName=codec->toUnicode(str);
     view->setWindowTitle(winName);
     view->show();
}
void YouXuanDockWidget::show_semisurvey()
{

    QSqlQueryModel *model= new QSqlTableModel;
    // Set character encoding to UTF8

    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    QTextCodec *codec =QTextCodec::codecForName("UTF-8");
    const char * str = "半结构化访谈";
    //const char * strcaption = "标题";
    const char * strCunname = "村名称";
    const char * strXiangname = "乡名称";
    QString tableName=codec->toUnicode(str);
  //  QString  caption =codec->toUnicode(strcaption);
    QString cunName=codec->toUnicode(strCunname);
    QString xiangName=codec->toUnicode(strXiangname);

    QString fullSql;
    fullSql = QString( "select * from '%1' where `%2`='%3' and `%4`='%5'" )
             .arg( tableName ).arg(cunName).arg(ui->comboBoxCunname->currentText())
             .arg(xiangName).arg(ui->comboBoxXiangname->currentText());
//    fullSql = QString( "select `%1` from '%2' where `%3`='%4' and `%5`='%6'" )
//             .arg(caption).arg( tableName ).arg(cunName).arg(ui->comboBoxCunname->currentText())
//             .arg(xiangName).arg(ui->comboBoxXiangname->currentText());
   // QMessageBox::information(NULL, "Title", fullSql, QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);

    model->setQuery(fullSql) ;//where id=101


    fangtang * wid = new fangtang(model);
    wid->setWindowTitle(tableName);
    wid->show();


}
void YouXuanDockWidget::show_specstatus()
{

        QSqlQueryModel *model= new QSqlTableModel;
        // Set character encoding to UTF8

        QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
        QTextCodec *codec =QTextCodec::codecForName("UTF-8");
        const char * str = "当地特殊情况";
        const char * strcaption = "标题";
        const char * strCunname = "村名称";
        const char * strXiangname = "乡名称";

        QString tableName=codec->toUnicode(str);
        QString  caption =codec->toUnicode(strcaption);
        QString cunName=codec->toUnicode(strCunname);
        QString xiangName=codec->toUnicode(strXiangname);

        QString fullSql;
        fullSql = QString( "select * from '%1' where `%2`='%3' and `%4`='%5'" )
                 .arg( tableName ).arg(cunName).arg(ui->comboBoxCunname->currentText())
                 .arg(xiangName).arg(ui->comboBoxXiangname->currentText());
    //    fullSql = QString( "select `%1` from '%2' where `%3`='%4' and `%5`='%6'" )
    //             .arg(caption).arg( tableName ).arg(cunName).arg(ui->comboBoxCunname->currentText())
    //             .arg(xiangName).arg(ui->comboBoxXiangname->currentText());
       // QMessageBox::information(NULL, "Title", fullSql, QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);

        model->setQuery(fullSql) ;//where id=101


        fangtang * wid = new fangtang(model);
        wid->setWindowTitle(tableName);
        wid->show();
}
void YouXuanDockWidget::show_ProblemStrategy()
{

    QSqlQueryModel *model= new QSqlTableModel;
    QSqlTableModel *modelPro_Strategy= new QSqlTableModel;
    // Set character encoding to UTF8

    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
     QTextCodec *codec =QTextCodec::codecForName("UTF-8");
    const char * strtable1 = "空心化程度";
    const char * strtable2 = "核心问题与整治策略";
    const char * strCunname = "村名称";
    const char * strXiangname = "乡名称";
    QString tableName1=codec->toUnicode(strtable1);
    QString tableName2=codec->toUnicode(strtable2);
    QString cunName=codec->toUnicode(strCunname);
    QString xiangName=codec->toUnicode(strXiangname);

     QString fullSql;
     fullSql = QString( "select * from '%1' where `%2`='%3' and `%4`='%5'" )
             .arg( tableName1 ).arg(cunName).arg(ui->comboBoxCunname->currentText())
             .arg(xiangName).arg(ui->comboBoxXiangname->currentText());




     // QMessageBox::information(NULL, "Title", fullSql, QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);

     model->setQuery(fullSql) ;
     fullSql = QString( " `%2`='%3' and `%4`='%5'" )
             .arg(cunName).arg(ui->comboBoxCunname->currentText())
             .arg(xiangName).arg(ui->comboBoxXiangname->currentText());

     modelPro_Strategy->setTable(tableName2);
     modelPro_Strategy->setFilter(fullSql);
     modelPro_Strategy->select();

    WenTi_CeLueForm * wid = new WenTi_CeLueForm(model,modelPro_Strategy);


     wid->show();

     QTableView *view = new QTableView;
     view->setModel(modelPro_Strategy);
     view->show();
}
void YouXuanDockWidget::show_InitStrategy()
{
    ChuBuFangAnForm * wid = new ChuBuFangAnForm();
    wid->show();
}
void YouXuanDockWidget::show_PublicOpinion()
{
    CunMinYIjianForm * wid = new CunMinYIjianForm();
    wid->show();
}
void YouXuanDockWidget::show_GovOpinion()
{
    ZhengFuYaoqiuForm * wid = new ZhengFuYaoqiuForm();
    wid->show();
}
void YouXuanDockWidget::show_FinalSolution()
{
    FinalFanganForm * wid = new FinalFanganForm();
    wid->show();
}
bool YouXuanDockWidget::createConnetion()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("demo.db");
    if (!db.open()) {
        QMessageBox::critical(0, qApp->tr("Cannot open database"),
            qApp->tr("Unable to establish a database connection.\n"
                     "This example needs SQLite support. Please read "
                     "the Qt SQL driver documentation for information how "
                     "to build it.\n\n"
                     "Click Cancel to exit."), QMessageBox::Cancel);

    }
}
