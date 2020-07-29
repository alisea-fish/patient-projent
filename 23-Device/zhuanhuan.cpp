#include "zhuanhuan.h"
#include "ui_zhuanhuan.h"
#include <QStackedLayout>
#include <QPushButton>
#include <QVBoxLayout>
#include"mainwidget.h"
#include"patientlistwidget.h"

zhuanhuan::zhuanhuan(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::zhuanhuan)
{
    ui->setupUi(this);
    setFixedSize(500, 400);
    mainwidget = new MainWidget;
    patientlistwidget = new PatientListWidget;
    stackLayout = new QStackedLayout;
    stackLayout->addWidget(mainwidget);
    stackLayout->addWidget(patientlistwidget);
    connect(mainwidget, &MainWidget::display, stackLayout, &QStackedLayout::setCurrentIndex);


    mainLayout = new QVBoxLayout;
    mainLayout->addLayout(stackLayout);
    setLayout(mainLayout);
}

zhuanhuan::~zhuanhuan()
{
    delete ui;
}
