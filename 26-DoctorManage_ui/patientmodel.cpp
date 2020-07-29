#include "patientmodel.h"
#include <QDebug>
#include <QSqlQuery>
#include <QSqlError>

PatientModel::PatientModel(QObject *parent, const QSqlDatabase &db) :
    QSqlTableModel(parent),
    db_(db)
{
}

bool PatientModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    qDebug() << "setData";
    bool ok = false;
    if(index.column() < 1 || index.column() > 4)
    {
        return false;
    }

    // 获patientId对应的QModelIndex
    QModelIndex primaryIndex = QSqlQueryModel::index(index.row(),0);
    qDebug() << primaryIndex;

    // 获取对应行的patientId的值
    int patientId = data(primaryIndex).toInt();

    if (index.column() == 1)
    {
        ok = this->setName(patientId, value.toString());
    }

    if (index.column() == 2)
    {
        ok = this->setSex(patientId, value.toString());
    }
    if (index.column() == 3)
    {
        ok = this->setBirth(patientId, value.toString());
    }
    if (index.column() == 4)
    {
        ok = this->setAge(patientId, value.toInt());
    }
    if (ok)
    {
        this->select();
    }
    else
    {
        qDebug() << "sql fail:";
    }
    return ok;

}

// 1、2、3列可编辑
Qt::ItemFlags  PatientModel::flags(const QModelIndex &index) const
{
//     qDebug() << "flags";
    // 获取index所在的flags
    Qt::ItemFlags flags = QSqlQueryModel::flags(index);
    if (index.column() == 1 || index.column() == 2 || index.column() == 3 || index.column() == 4)
    {
        flags |= Qt::ItemIsEditable;
    }
    return flags;
}

bool PatientModel::setName(int id, QString name)
{
    QSqlQuery query(db_);
    query.prepare("update patient set name=:name where patientId=:id;");
    query.bindValue(":name", name);
    query.bindValue(":id", id);
//    if (!query.exec())
//    {
//        qDebug() << "error:" << query.lastError().text();
//        return false;
//    }
    return query.exec();
}

bool PatientModel::setSex(int id, QString sex)
{
    QSqlQuery query(db_);
    query.prepare("update patient set sex=:sex where patientId=:id;");
    query.bindValue(":sex", sex);
    query.bindValue(":id", id);
    return query.exec();
}

bool PatientModel::setBirth(int id, QString birth)
{
    birth = QString('YYYY-MM-DD');
    QSqlQuery query(db_);
    query.prepare("update patient set birth=:birth where patientId=:id;");
    query.bindValue(":birth", birth);
    query.bindValue(":id", id);
    return query.exec();
}

bool PatientModel::setAge(int id, int age)
{
    QSqlQuery query(db_);
    query.prepare("update patient set age=((strftime('%Y', 'now') - strftime('%Y', Birth_Date)) - (strftime('%m-%d', 'now') < strftime('%m-%d', Birth_Date)));");
    query.bindValue(":age", age);
    query.bindValue(":id", id);
    return query.exec();
}
