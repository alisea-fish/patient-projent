#include "patientlistwidget.h"
#include "ui_patientlistwidget.h"
#include <QtDebug>

PatientListWidget::PatientListWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::PatientListWidget)
{
    ui->setupUi(this);
    // 1.加载数据库驱动
    db = QSqlDatabase::addDatabase("QSQLITE");
    // 2.设置数据库名
    db.setDatabaseName("F:/Qt Project/test.db");
    // 3.打开数据库
    if (!db.open())
    {
        qDebug() << "打开失败";
    }
    // 1.创建模型对象
    model = new QSqlTableModel(this);

    // 2.关联模型与表格
    model->setTable("patient");
    model->select();

    // 3.创建视图并关联模型与视图
    ui->tableView->setModel(model);
    //ui->patient_tableview->resizeColumnsToContents();

    // 4.修改视图的显示方式
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID号"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("姓名"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("性别"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("生日"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("年龄"));

}

PatientListWidget::~PatientListWidget()
{
    delete ui;
}

