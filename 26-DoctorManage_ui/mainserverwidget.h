#ifndef MAINSERVERWIDGET_H
#define MAINSERVERWIDGET_H

#include <QWidget>

namespace Ui {
class MainServerWidget;
}

class MainServerWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MainServerWidget(QWidget *parent = 0);
    ~MainServerWidget();

public slots:
    void displayMessage(char* buffer);

private slots:
    void on_startButton_clicked();

    void on_stopButton_clicked();

private:
    Ui::MainServerWidget *ui;
};

#endif // MAINSERVERWIDGET_H
