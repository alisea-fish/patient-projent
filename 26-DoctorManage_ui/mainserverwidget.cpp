#include "mainserverwidget.h"
#include "ui_mainserverwidget.h"
#include "server.h"
#include <QDebug>

MainServerWidget::MainServerWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainServerWidget)
{
    ui->setupUi(this);
}

MainServerWidget::~MainServerWidget()
{
    delete ui;
}

// 自动连接
void MainServerWidget::on_startButton_clicked()
{
    // 获取服务器对象
    Server* ser = Server::getServerInstance();
    quint16 port = ui->portLineEdit->text().toUInt();
    ser->start(port);

    // 修改界面
    ui->startButton->setEnabled(false);
    ui->stopButton->setEnabled(true);
}

void MainServerWidget::on_stopButton_clicked()
{
    // 获取服务器对象
    Server* ser = Server::getServerInstance();
    ser->stop();

    // 修改界面
    ui->startButton->setEnabled(true);
    ui->stopButton->setEnabled(false);

}



static unsigned short ecgData[873];
void MainServerWidget::displayMessage(char *buffer)
{
    char serial[24] = {0};
    memcpy(serial, buffer, 24);
    memcpy(ecgData, buffer+24, 1746);
    delete[] buffer;
    qDebug() << serial;

}
