#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    ui->pushButtonStart->setEnabled(true);
    ui->pushButtonStop->setEnabled(false);

}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_pushButtonStart_clicked()
{
    ui->pushButtonStop->setEnabled(true);
    ui->pushButtonStart->setEnabled(false);
    QVariantMap args;       //我的ubuntu ip是192.168.232.131 ，配置的rtmp端口1935 开启的应用名叫hls1
    args["filePath"] =  "rtmp://192.168.232.131:1935/hls1/test1"; ///test..flv//"test2.flv";//

    args["width"] = 1280;
    args["height"] = 720;
    args["fps"] = 5;
    args["audioBitrate"] = 128000;
    args["offset_x"] = 100;
    args["offset_y"] = 100;


    m_avrecord.Init(args);
    m_avrecord.Start();
}

void Widget::on_pushButtonStop_clicked()
{
    ui->pushButtonStop->setEnabled(false);
    ui->pushButtonStart->setEnabled(true);
    m_avrecord.Stop();
}
