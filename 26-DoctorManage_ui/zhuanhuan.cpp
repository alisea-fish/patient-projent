#include "zhuanhuan.h"
#include "ui_zhuanhuan.h"
#include "mainwidget.h"
#include "denglu.h"
#include <QStackedLayout>
#include <QPushButton>
#include <QVBoxLayout>

Zhuanhuan::Zhuanhuan(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Zhuanhuan)
{
    ui->setupUi(this);
    setFixedSize(500, 400);
    mainwidget = new MainWidget;
    denglu = new Denglu;
    stackLayout = new QStackedLayout;
    stackLayout->addWidget(denglu);
    stackLayout->addWidget(mainwidget);
    connect(denglu, &Denglu::display, stackLayout, &QStackedLayout::setCurrentIndex);


    mainLayout = new QVBoxLayout;
    mainLayout->addLayout(stackLayout);
    setLayout(mainLayout);
}

Zhuanhuan::~Zhuanhuan()
{
    delete ui;
}
