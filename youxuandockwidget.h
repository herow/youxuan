#ifndef YOUXUANDOCKWIDGET_H
#define YOUXUANDOCKWIDGET_H

#include <QDockWidget>
class QDataWidgetMapper;
class QSqlTableModel;
class ChuBuFangAnForm;
class QSqlQueryModel;
class WenTi_CeLueForm;
class fangtang;
class FinalFanganForm;
namespace Ui {
class YouXuanDockWidget;
}

class YouXuanDockWidget : public QDockWidget
{
    Q_OBJECT

public:
    explicit YouXuanDockWidget(QWidget *parent = 0);
    ~YouXuanDockWidget();

private:
    Ui::YouXuanDockWidget *ui;
    QSqlTableModel *modelPro_Strategy;
    QSqlTableModel *model_InitialStrategy;
    QSqlTableModel *model_FinalStrategy;
    ChuBuFangAnForm *chubufangan;
    QSqlQueryModel *model_strategy;
    QSqlQueryModel *model_PublicOpinion;
    QSqlQueryModel *model_GovOpinion;
    fangtang *wid_PublicOpinion;
    fangtang *wid_GovOpinion;
    WenTi_CeLueForm *wid_wenti_celue;
    FinalFanganForm *wid_finalStrategy;
private slots:
    void show_kongxin_status();
    void show_surveyForm();
    void show_picturecollect();
    void show_ProblemStrategy();
    void show_specstatus();
    void show_semisurvey();
    void show_InitStrategy();
    void show_PublicOpinion();
    void show_GovOpinion();
    void show_FinalSolution();
private:
    bool createConnetion();
    QDataWidgetMapper *mapper;
};

#endif // YOUXUANDOCKWIDGET_H
