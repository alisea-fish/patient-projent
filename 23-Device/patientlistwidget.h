#ifndef PATIENTLISTWIDGET_H
#define PATIENTLISTWIDGET_H

#include <QWidget>
#include <QSqlQueryModel>
#include <QSqlTableModel>
#include <QTableView>

QT_BEGIN_NAMESPACE
namespace Ui { class PatientListWidget; }
QT_END_NAMESPACE

class PatientListWidget : public QWidget
{
    Q_OBJECT

public:
    PatientListWidget(QWidget *parent = nullptr);
    ~PatientListWidget();

private:
    Ui::PatientListWidget *ui;
    QSqlDatabase db;
    QSqlTableModel *model;
};
#endif // PATIENTLISTWIDGET_H
