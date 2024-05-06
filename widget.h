#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "avrecord.h"

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void on_pushButtonStart_clicked();

    void on_pushButtonStop_clicked();

private:
    Ui::Widget *ui;
    AVRecord m_avrecord;
};

#endif // WIDGET_H
