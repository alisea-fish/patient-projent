#ifndef DENGLU_H
#define DENGLU_H

#include <QWidget>
#include <QSqlQueryModel>
#include <QSqlDatabase>
#include <QSqlRelationalTableModel>
#include<QLabel>

class MainWidget;

namespace Ui {
class Denglu;
}

class Denglu : public QWidget
{
    Q_OBJECT

public:
    explicit Denglu(QWidget *parent = nullptr);
    ~Denglu();

signals:
    void display(int number);

private slots:
    void on_pushButton_clicked();

private:
    Ui::Denglu *ui;
    QSqlQueryModel* model;
    QSqlDatabase db;
    MainWidget *mainwidget;
};

#endif // DENGLU_H
