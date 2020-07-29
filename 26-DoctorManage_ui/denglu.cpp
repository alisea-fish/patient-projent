#include "denglu.h"
#include "ui_denglu.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

Denglu::Denglu(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Denglu)
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

        return;
    }
    // 4.创建模型对象
    //model = new QSqlQueryModel(this);
    //model = new PatientModel(this, db);

    // 5.创建视图：ui->tableView

    // 6.关联模型与表格
    //model->setQuery("select * from doctor;", db);
}

Denglu::~Denglu()
{
    delete ui;
}

void Denglu::on_pushButton_clicked()
{
    QString content = ui->lineEdit->text();
    QString sql;
    sql = QString("select * from doctor where mobilenumbe='%1';").arg(content);
    //model->setQuery(sql);
    QSqlQuery query(db);
    query.exec(sql);
    if (!query.next())
    {
        //messageLabel = new QLabel("用户不存在!", this);
        //messageLabel->move(100, 100);
        //messageLabel->resize(200, 50);
        qDebug() << "用户不存在!";
        return;
    }
    else
    {
        QString content1 = ui->lineEdit_2->text();
        QString sql1;
        sql1 = QString("select * from doctor where password='%1' and mobilenumbe='%2';").arg(content1).arg(content);
        query.exec(sql1);
        if (query.next())
        {

            //messageLabel->move(100, 100);
            //messageLabel->resize(200, 50);
            qDebug() << "登录成功!";
        }
        else
        {
            //messageLabel = new QLabel("登录成功!", this);
            //messageLabel->move(100, 100);
            //messageLabel->resize(200, 50);
            qDebug() << "密码错误";
            return;
        }
    }
    emit display(1);

}
