#ifndef ZHUANHUAN_H
#define ZHUANHUAN_H

#include <QWidget>

class MainWidget;
class Denglu;
class QStackedLayout;
class QVBoxLayout;

namespace Ui {
class Zhuanhuan;
}

class Zhuanhuan : public QWidget
{
    Q_OBJECT

public:
    explicit Zhuanhuan(QWidget *parent = nullptr);
    ~Zhuanhuan();

private:
    Ui::Zhuanhuan *ui;
    MainWidget *mainwidget;
    Denglu *denglu;
    QStackedLayout *stackLayout;
    QVBoxLayout *mainLayout;

};

#endif // ZHUANHUAN_H
