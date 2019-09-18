#include "feedercontrol.h"
#include "ui_feedercontrol.h"

FeederControl::FeederControl(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FeederControl)
{
    ui->setupUi(this);
}

FeederControl::~FeederControl()
{
    delete ui;
}
