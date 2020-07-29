#ifndef WAVE_H
#define WAVE_H

#include <QWidget>
#include<QPixmap>

class wave : public QWidget
{
    Q_OBJECT
public:
    explicit wave(QWidget *parent = nullptr);


public slots:
    void refreshPixmap();


protected:
    void paintEvent(QPaintEvent *event) override;

private:
    QPixmap * pix_;

};

#endif // WAVE_H
