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
    connect( ui->comboBoxXiangname, SIGNAL(currentIndexChanged(int)),this,SLOT(setSelection(int)));
    connect( ui->comboBoxCunname, SIGNAL(currentIndexChanged(int)),this,SLOT(setSelection(int)));

//    if (!createConnection())
//        return  ;
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
     QTextCodec *codec =QTextCodec::codecForName("UTF-8");

    const char * strtable2 = "核心问题与整治策略";

    QString tableName2=codec->toUnicode(strtable2);
    model_youxuan= new QSqlTableModel;
    model_youxuan->setTable(tableName2);
 //   model_youxuan->setEditStrategy(QSqlTableModel::OnManualSubmit);


    mapper = new QDataWidgetMapper(this);
    mapper->setModel(model_youxuan);
    mapper->setItemDelegate(new ComboBoxDelegate(this));
    mapper->addMapping(ui->comboxKongxc,6);
    mapper->addMapping(ui->comboxZhengzhi, 7);
    mapper->addMapping(ui->lineEditZonghushu, 8);
    mapper->addMapping(ui->lineEditTongyi, 9);
    mapper->addMapping(ui->lineEditFandui, 10);
    mapper->addMapping(ui->comboxGaizaoyiyuan, 11);

    setSelection(0);


    modelPro_Strategy= new QSqlTableModel;
    model_InitialStrategy =new QSqlTableModel;
    model_FinalStrategy =new QSqlTableModel;
   // chubufangan= new ChuBuFangAnForm(modelPro_Strategy);
    model_SurveyForm = new QSqlQueryModel;
    model_SemiSurvey = new QSqlQueryModel;
    model_SpecStatus = new QSqlQueryModel;
    model_strategy= new QSqlQueryModel;
    model_PublicOpinion=new QSqlQueryModel;
    model_GovOpinion=new QSqlQueryModel;
   // wid_wenti_celue = new WenTi_CeLueForm(model_strategy,modelPro_Strategy);
}
void YouXuanDockWidget::setSelection(int idx)
{
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    QTextCodec *codec =QTextCodec::codecForName("UTF-8");
    const char * strCunname = "村名称";
    const char * strXiangname = "乡名称";
    QString cunName=codec->toUnicode(strCunname);
    QString xiangName=codec->toUnicode(strXiangname);

    QString fullSql = QString( " `%1`='%2' and `%3`='%4'" )
            .arg(cunName).arg(ui->comboBoxCunname->currentText())
            .arg(xiangName).arg(ui->comboBoxXiangname->currentText());


    model_youxuan->setFilter(fullSql);
    model_youxuan->select();
 //   mapper->setModel(model_youxuan);
  //  mapper->setItemDelegate(new ComboBoxDelegate(this));
//    mapper->addMapping(ui->comboxKongxc,6);
//    mapper->addMapping(ui->comboxZhengzhi, 7);
//    mapper->addMapping(ui->lineEditZonghushu, 8);
//    mapper->addMapping(ui->lineEditTongyi, 9);
//    mapper->addMapping(ui->lineEditFandui, 10);
//    mapper->addMapping(ui->comboxGaizaoyiyuan, 11);

    mapper->toFirst();
}
YouXuanDockWidget::~YouXuanDockWidget()
{
    delete ui;
    delete model_youxuan;
    delete model_SurveyForm;
    delete model_SemiSurvey;
    delete model_SpecStatus;
    delete modelPro_Strategy;
    delete model_strategy;
    delete model_PublicOpinion;
    delete model_GovOpinion;
    delete model_FinalStrategy;
    delete chubufangan;
    delete wid_SemiSurvey;
    delete wid_SpecStatus;
    delete wid_wenti_celue;
    delete chubufangan;
    delete wid_PublicOpinion;
    delete wid_GovOpinion;
    delete wid_finalStrategy;
    delete wid_picview;
}

void YouXuanDockWidget::show_kongxin_status()
{

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

    model_SurveyForm->setQuery(fullSql) ;//where id=101



    QTableView *view = new QTableView;
    view->setModel(model_SurveyForm);
    view->setGeometry(QRect(0,0,900,500));
    view->show();
}
void YouXuanDockWidget::show_picturecollect()
{
//     ImageCollection * wid = new ImageCollection();
//     wid->show();

     QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
     QTextCodec *codec =QTextCodec::codecForName("UTF-8");
     const char * str = "数据图件";
     QString winName=codec->toUnicode(str);

     wid_picview=new View(winName,ui->comboBoxXiangname->currentText(),
                         ui->comboBoxCunname->currentText());
     wid_picview->setWindowTitle(winName);
     wid_picview->show();
}
void YouXuanDockWidget::show_semisurvey()
{

    //QSqlQueryModel *model= new QSqlTableModel;
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

    model_SemiSurvey->setQuery(fullSql) ;//where id=101


    wid_SemiSurvey = new fangtang(model_SemiSurvey);
    wid_SemiSurvey->setWindowTitle(tableName);
    wid_SemiSurvey->show();


}
void YouXuanDockWidget::show_specstatus()
{

        //QSqlQueryModel *model= new QSqlTableModel;
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

        model_SpecStatus->setQuery(fullSql) ;//where id=101
        wid_SpecStatus = new fangtang(model_SpecStatus);
        wid_SpecStatus->setWindowTitle(tableName);
        wid_SpecStatus->show();
}
void YouXuanDockWidget::show_ProblemStrategy()
{

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

     model_strategy->setQuery(fullSql) ;
//     fullSql = QString( " `%2`='%3' and `%4`='%5'" )
//             .arg(cunName).arg(ui->comboBoxCunname->currentText())
//             .arg(xiangName).arg(ui->comboBoxXiangname->currentText());

//     modelPro_Strategy->setTable(tableName2);
//     modelPro_Strategy->setFilter(fullSql);
//     modelPro_Strategy->select();



    wid_wenti_celue = new WenTi_CeLueForm(model_strategy,model_youxuan);
     wid_wenti_celue->show();


}
void YouXuanDockWidget::show_InitStrategy()
{

    // Set character encoding to UTF8

    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
     QTextCodec *codec =QTextCodec::codecForName("UTF-8");
   // const char * strtable1 = "空心化程度";
    const char * strtable2 = "核心问题与整治策略";
    const char * strCunname = "村名称";
    const char * strXiangname = "乡名称";
  //  QString tableName1=codec->toUnicode(strtable1);
    QString tableName2=codec->toUnicode(strtable2);
    QString cunName=codec->toUnicode(strCunname);
    QString xiangName=codec->toUnicode(strXiangname);

//     QString fullSql;

//     fullSql = QString( " `%2`='%3' and `%4`='%5'" )
//             .arg(cunName).arg(ui->comboBoxCunname->currentText())
//             .arg(xiangName).arg(ui->comboBoxXiangname->currentText());

//     model_InitialStrategy->setTable(tableName2);
//     model_InitialStrategy->setFilter(fullSql);
//     model_InitialStrategy->select();

     chubufangan= new ChuBuFangAnForm(model_youxuan);


     chubufangan->show();


}
void YouXuanDockWidget::show_PublicOpinion()
{
//    CunMinYIjianForm * wid = new CunMinYIjianForm();
//    wid->show();

    // Set character encoding to UTF8

    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    QTextCodec *codec =QTextCodec::codecForName("UTF-8");
    const char * str = "村民意见";
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

    model_PublicOpinion->setQuery(fullSql) ;//where id=101


    wid_PublicOpinion = new fangtang(model_PublicOpinion);
    wid_PublicOpinion->setWindowTitle(tableName);
    wid_PublicOpinion->show();
//    QTableView *view = new QTableView;
//    view->setModel(model);
//    //view->horizontalHeader()->hide();
//    view->show();

}
void YouXuanDockWidget::show_GovOpinion()
{
//    ZhengFuYaoqiuForm * wid = new ZhengFuYaoqiuForm();
//    wid->show();
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    QTextCodec *codec =QTextCodec::codecForName("UTF-8");
    const char * str = "政府意见";
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

    model_GovOpinion->setQuery(fullSql) ;//where id=101


    wid_GovOpinion = new fangtang(model_GovOpinion);
    wid_GovOpinion->setWindowTitle(tableName);
    wid_GovOpinion->show();
}
void YouXuanDockWidget::show_FinalSolution()
{

//    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
//     QTextCodec *codec =QTextCodec::codecForName("UTF-8");
//   // const char * strtable1 = "空心化程度";
//    const char * strtable2 = "核心问题与整治策略";
//    const char * strCunname = "村名称";
//    const char * strXiangname = "乡名称";
//  //  QString tableName1=codec->toUnicode(strtable1);
//    QString tableName2=codec->toUnicode(strtable2);
//    QString cunName=codec->toUnicode(strCunname);
//    QString xiangName=codec->toUnicode(strXiangname);

//     QString fullSql;

//     fullSql = QString( " `%2`='%3' and `%4`='%5'" )
//             .arg(cunName).arg(ui->comboBoxCunname->currentText())
//             .arg(xiangName).arg(ui->comboBoxXiangname->currentText());

//     model_FinalStrategy->setTable(tableName2);
//     model_FinalStrategy->setFilter(fullSql);
//     model_FinalStrategy->select();

     wid_finalStrategy= new FinalFanganForm(model_youxuan);
     wid_finalStrategy->show();
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
void YouXuanDockWidget::closeEvent(QCloseEvent *event)
{
//    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
//    QTextCodec *codec =QTextCodec::codecForName("UTF-8");
//    const char * strcaption = "提示";
//    const char * strcontent = "是否对数据进行保存？" ;
//    const char * strok= "是";
//    const char * strno= "否";
//    const char * strcancel = "取消";
//    QString strCap=codec->toUnicode(strcaption);
//    QString strCont=codec->toUnicode(strcontent);
//    QString strOkbtn=codec->toUnicode(strok);
//    QString strNobtn=codec->toUnicode(strno);
//    QString strCancelbtn=codec->toUnicode(strcancel);

//    int r=QMessageBox::question(this,strCap,strCont,
//   strOkbtn,strNobtn);

//    QMessageBox box(QMessageBox::warning,"strCap","strCont");
//    box.setStandardButtons (QMessageBox::Ok|QMessageBox::Cancel);
//    box.setButtonText (QMessageBox::Ok,strOkbtn);
//    box.setButtonText (QMessageBox::Cancel,strCancelbtn);


//    if (r==0)
//    {
        mapper->submit();
        event->accept();
//    }
//    else
//    {
//        event->accept();
//    }
}
