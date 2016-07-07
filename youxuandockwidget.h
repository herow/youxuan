#ifndef YOUXUANDOCKWIDGET_H
#define YOUXUANDOCKWIDGET_H

#include <QDockWidget>

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
};

#endif // YOUXUANDOCKWIDGET_H
