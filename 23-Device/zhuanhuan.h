#ifndef ZHUANHUAN_H
#define ZHUANHUAN_H

#include <QWidget>

class MainWidget;
class PatientListWidget;
class QStackedLayout;
class QVBoxLayout;

namespace Ui {
class zhuanhuan;
}

class zhuanhuan : public QWidget
{
    Q_OBJECT

public:
    explicit zhuanhuan(QWidget *parent = nullptr);
    ~zhuanhuan();

private:
    Ui::zhuanhuan *ui;
    MainWidget *mainwidget;
    PatientListWidget *patientlistwidget;
    QStackedLayout *stackLayout;
    QVBoxLayout *mainLayout;
};

#endif // ZHUANHUAN_H
