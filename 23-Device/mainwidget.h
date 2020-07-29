#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <QTimer>
#include "tcpsocket.h"

class PatientListWidget;

namespace Ui {
class MainWidget;
}

class MainWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MainWidget(QWidget *parent = 0);
    ~MainWidget();

signals:
    void display(int number);

private slots:
    void on_connectButton_clicked();

    void sendEcgWava();
    void displayMessage(QString content);

    void on_sendButton_2_clicked();

private:
    Ui::MainWidget *ui;
    TcpSocket* socket;
    QTimer* timer;
    PatientListWidget *patientlistwidget;
};

#endif // MAINWIDGET_H
