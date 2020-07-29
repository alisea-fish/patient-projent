#ifndef MAINWIDGET_H
#define MAINWIDGET_H


#include <QWidget>
#include<QPixmap>

class MainWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MainWidget(QWidget *parent = nullptr);
//    MainWidget(QWidget *parent = nullptr);
//    ~MainWidget();
public slots:
    void refreshPixmap();


protected:
    void paintEvent(QPaintEvent *event) override;

private:
    QPixmap * pix_;

};
#endif // MAINWIDGET_H
