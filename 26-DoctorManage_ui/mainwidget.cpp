#include "mainwidget.h"
#include "ui_mainwidget.h"
#include "patientmodel.h"
#include <QDebug>
#include <QSqlQuery>
#include <QSqlError>
#include <QVariant>
#include <QMessageBox>
#include <QSqlRelation>
#include <QSqlRelationalDelegate>
#include <QSqlTableModel>
#include <QSqlRecord>
#include <QTimer>
#include <QSqlDatabase>
#include "business.h"
#include "database.h"
#include<QPainter>
#include<QDateTime>
#include"wave.h"

MainWidget::MainWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWidget)
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(0);

    ui->recvButton->setMinimumHeight(30);
    ui->patientButton->setMinimumHeight(30);
    ui->deviceButton->setMinimumHeight(30);
    ui->bindButton->setMinimumHeight(30);
    ui->realtimeButton->setMinimumHeight(30);
    ui->historyButton->setMinimumHeight(30);


    // 1.加载数据库驱动
    db = QSqlDatabase::addDatabase("QSQLITE");
    // 2.设置数据库名
    db.setDatabaseName("F:/Qt Project/test.db");
    // 3.打开数据库
    if (!db.open())
    {
        qDebug() << "打开失败";
    }

    //一
    //病人列表
    // 1.创建模型对象
    model = new PatientModel(this, db);

    // 2.关联模型与表格
    model->setTable("patient");
    model->select();

    // 3.创建视图并关联模型与视图
    ui->patient_tableview->setModel(model);
    //ui->patient_tableview->resizeColumnsToContents();

    // 4.修改视图的显示方式
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID号"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("姓名"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("性别"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("生日"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("年龄"));

    //二
    //设备列表操作
    bs1 = new Business(this);
    bs2 = new Business(this);
    bs3 = new Business(this);

    devicemodel = new QSqlQueryModel(this);
    devicemodel-> setQuery("select * from device;");
    //设置15秒刷新一次
    QTimer *timer = new QTimer(this);
    connect(timer,&QTimer::timeout,
            this,&MainWidget::on_commandLinkButton_clicked);
    timer->start(15000);

    //三
    //病人设备绑定
    patientComboBoxModel = new QSqlQueryModel(this);
    deviceComboBoxModel = new QSqlQueryModel(this);

    ui->patientComboBox->setModel(patientComboBoxModel);
    ui->deviceCombox->setModel(deviceComboBoxModel);

    patientComboBoxModel->setQuery("select patientId from patient where patientId not in (select patientId from patient_device);", db);
    deviceComboBoxModel->setQuery("select dev_serial from device where dev_id not in (select devId from patient_device);", db);

    //绑定列表显示
    patientDeviceModel = new QSqlRelationalTableModel(this,db);
    patientDeviceModel -> setEditStrategy(QSqlTableModel::OnManualSubmit);
    //设置模型操作的表
    patientDeviceModel -> setTable("patient_device");
    patientDeviceModel -> setRelation(1,QSqlRelation("patient","patientId","name"));
    patientDeviceModel -> setRelation(2,QSqlRelation("device","dev_id","dev_serial"));
    patientDeviceModel -> select();
    ui -> patient_device_tableview ->setModel(patientDeviceModel);
    //设置代理
    ui -> patient_device_tableview ->setItemDelegate(new QSqlRelationalDelegate(ui->patient_device_tableview));




    //四
    //实时波形显示




    //五
    //历史波形显示






}

MainWidget::~MainWidget()
{
    delete ui;
}

//切换界面
void MainWidget::on_recvButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWidget::on_patientButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);

}

void MainWidget::on_deviceButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}

void MainWidget::on_bindButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
}

void MainWidget::on_realtimeButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(4);
}

void MainWidget::on_historyButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(5);

}

//一
//病人列表操作
void MainWidget::on_addButton_clicked()
{
    QSqlQuery query(db);
    if (!query.exec("insert into patient values(null, 'Merry', '女', '1997-11-28',null);"))
    {
        qDebug() << "insert fail" << query.lastError().text();
        return ;
    }
    query.exec("update patient set age=((strftime('%Y', 'now') - strftime('%Y', Birth_Date)) - (strftime('%m-%d', 'now') < strftime('%m-%d', Birth_Date)));");

    //model->setQuery("select * from patient;", db);

//    int rowNum = model->rowCount();
//    int id = 6;
//    //添加一行
//    model->insertRow(rowNum);
//    model->setData(model->index(rowNum,0),id);
//    //提交
    model->submitAll();



}

void MainWidget::on_removeButton_clicked()
{
    int curRow = ui->patient_tableview->currentIndex().row();
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model->removeRow(curRow);
    int ok = QMessageBox::warning(this,tr("删除当前行"),tr("你确定删除当前行吗?"),QMessageBox::Yes,QMessageBox::No);
    if(ok==QMessageBox::No)
    {
        model->revertAll();//选no则撤销
    }
    else
    {
        model->submitAll();//选yes在数据库中删除该行
    }

}

void MainWidget::on_updateButton_clicked()
{
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model->database().transaction();
    if(model->submitAll())
    {
        if(model->database().commit())//提交
        {
            QMessageBox::information(this,tr("patientmodel"),tr("修改成功！"));
        }
        else
        {
            model->database().rollback();//回滚
            QMessageBox::warning(this,tr("patientmodel"),tr("数据库错误：%1").arg(model->lastError().text()),QMessageBox::Ok);
        }
    }

}

void MainWidget::on_selectButton_clicked()
{
    QString content = ui->patient_lineEdit->text();
    QString sql;
    if (content.isEmpty())
    {
        model->setTable("patient");
        model->select();
    }
    else
    {
        model->setFilter(QString("name='%1'").arg(content));
        model->select();
    }

}

//二
//设备列表
void MainWidget::on_commandLinkButton_clicked()
{
    bs1->deviceLogin("dev-01");
    bs2->deviceLogin("dev-02");
    bs3->deviceLogin("dev-03");
    devicemodel-> setQuery("select * from device;");
    ui->device_tableview->setModel(devicemodel);
    ui->device_tableview->resizeColumnsToContents();
}

//三
// 绑定
void MainWidget::on_bindOpButton_clicked()
{
    // 病人id
    int patientId = ui->patientComboBox->currentText().toInt();

    // 设备id
    int devId;
    QString serial = ui->deviceCombox->currentText();
    QSqlQuery query(db);
    query.prepare("select dev_id from device where dev_serial = :serial;");
    query.bindValue(":serial", QVariant(serial));
    if (!query.exec())
    {
        qDebug() << "绑定失败！";
        QMessageBox::warning(this, "提示", "绑定失败", QMessageBox::Ok);
        return;
    }
    if (query.next())
    {
        devId = query.value(0).toInt();
    }

    // 绑定
    query.prepare("insert into patient_device values(null, :patientId, :devId);");
    query.bindValue(":patientId", patientId);
    query.bindValue(":devId", devId);
    if (!query.exec())
    {
        qDebug() << "绑定失败";
        return ;
    }
    qDebug() << "绑定成功";

    // 刷新绑定列表模型

    // 刷新病人comboBox模型 // 刷新设备comboBox模型
    patientComboBoxModel->setQuery("select patientId from patient where patientId not in (select patientId from patient_device);", db);
    deviceComboBoxModel->setQuery("select dev_serial from device where dev_id not in (select devId from patient_device);", db);
    patientDeviceModel->setTable("patient_device");
    patientDeviceModel->select();
    ui -> patient_device_tableview ->setModel(patientDeviceModel);
}

void MainWidget::on_deletebutton_clicked()
{
    int RowNum = ui->patient_device_tableview->currentIndex().row();
    patientDeviceModel->setEditStrategy(QSqlRelationalTableModel::OnManualSubmit);
    patientDeviceModel->removeRow(RowNum);
    int ok = QMessageBox::warning(this,tr("删除当前行"),tr("你确定删除当前行吗?"),QMessageBox::Yes,QMessageBox::No);
    if(ok==QMessageBox::No)
    {
        patientDeviceModel->revertAll();//选no则撤销
    }
    else
    {
        patientDeviceModel->submitAll();//选yes在数据库中删除该行
    }
}

//新加的

void MainWidget::on_widget_2_customContextMenuRequested(const QPoint &pos)
{

    wave a;
    a.show();

}

