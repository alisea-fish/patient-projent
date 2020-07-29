#ifndef PATIENTMODEL_H
#define PATIENTMODEL_H

#include <QSqlQueryModel>
#include <QSqlTableModel>

class PatientModel : public QSqlTableModel
{
    Q_OBJECT
public:
    PatientModel(QObject *parent = nullptr,const QSqlDatabase& db = QSqlDatabase());

    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);
    Qt::ItemFlags flags(const QModelIndex &index) const;

    bool setName(int id, QString name);
    bool setSex(int id, QString sex);
    bool setBirth(int id, QString birth);
    bool setAge(int id, int age);

private:
    QSqlDatabase db_;

};

#endif // PATIENTMODEL_H
