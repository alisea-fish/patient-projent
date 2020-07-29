#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include "business.h"
#include <QWidget>
#include <QSqlDatabase>
#include <QSqlQueryModel>
#include <QSqlRelationalTableModel>
#include<QPixmap>  //改过

namespace Ui {
class MainWidget;
}
class QSqlTableModel;
class MainWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MainWidget(QWidget *parent = 0);
    ~MainWidget();

private slots:
    //更改界面
    void on_patientButton_clicked();

    void on_deviceButton_clicked();

    void on_realtimeButton_clicked();

    void on_historyButton_clicked();

    void on_bindButton_clicked();

    //病人列表操作
    void on_addButton_clicked();

    void on_removeButton_clicked();

    void on_updateButton_clicked();

    void on_selectButton_clicked();

    //设备列表操作
    void on_deletebutton_clicked();

    //病人与设备绑定
    void on_bindOpButton_clicked();

    void on_commandLinkButton_clicked();


    void on_widget_2_customContextMenuRequested(const QPoint &pos);


    void on_recvButton_clicked();

private:
    Ui::MainWidget *ui;
    QSqlDatabase db;
    //病人列表操作
    QSqlTableModel *model;

    //设备列表操作
    Business *bs1;
    Business *bs2;
    Business *bs3;
    QSqlQueryModel *devicemodel;

    //病人设备绑定
    QSqlQueryModel *patientComboBoxModel;
    QSqlQueryModel *deviceComboBoxModel;
    QSqlRelationalTableModel *patientDeviceModel;
    QPixmap * pix_;//改过


};

#endif // MAINWIDGET_H
