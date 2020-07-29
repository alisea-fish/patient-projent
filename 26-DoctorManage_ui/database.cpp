#include "database.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QVariant>
#include <QDebug>

Database::Database(QObject *parent) : QObject(parent)
{
    // 0. 判断数据库是否已经添加
    if (QSqlDatabase::contains("device_connection"))
    {
        db = QSqlDatabase::database("device_connection");
    }
    else
    {
        // 1.加载数据库驱动
        db = QSqlDatabase::addDatabase("QSQLITE", "device_connection");

        // 2. 设置数据库名
        db.setDatabaseName("F:/Qt Project/test.db");
    }
}

Database *Database::getDatabaseInstance()
{
    static Database database;
    return &database;
}

bool Database::queryDeviceBySerial(QString serial)
{
    bool ret = true;
    // 1.打开数据库
    if (!db.open())
    {
        return false;
    }

    // 2.执行sql
    QString sql = "select * from device where dev_serial = :serial";
    QSqlQuery query(db);
    query.prepare(sql);
    query.bindValue(":serial", QVariant(serial));
    if (!query.exec())
    {
        qDebug() << "select fail:" << query.lastError().text();
        ret = false;
        goto retTag;
    }
    //query.size() == 0;
    if (!query.next())
    {
        ret = false;
    }
    // 3.关闭数据库
retTag:
    db.close();
    return ret;
}

bool Database::insertDevice(QString serial)
{
    bool ret = true;

    // 1.打开数据库
    if (!db.open())
    {
        return false;
    }
     // 2.执行sql
    QString sql = "insert into device values(NULL, :serial, datetime('now','localtime'));";
    QSqlQuery query(db);
    query.prepare(sql);
    query.bindValue(":serial", QVariant(serial));
    if (!query.exec())
    {
        qDebug() << "insert fail:" << query.lastError().text();
        ret = false;
    }

    // 3.关闭数据库
    db.close();
    return ret;

}

bool Database::updateDeviceRefresh(QString serial)
{
    bool ret = true;

    // 1.打开数据库
    if (!db.open())
    {
        return false;
    }
     // 2.执行sql
    QString sql = "update device set refresh = datetime('now', 'localtime') where dev_serial = :serial;";
    QSqlQuery query(db);
    query.prepare(sql);
    query.bindValue(":serial", QVariant(serial));
    if (!query.exec())
    {
        qDebug() << "insert fail:" << query.lastError().text();
        ret = false;
    }
    // 3.关闭数据库
    db.close();
    return ret;
}
