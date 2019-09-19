#include "feedercontrol.h"
#include "ui_feedercontrol.h"

FeederControl::FeederControl(Feeder &feeder, QWidget *parent) :
    QWidget(parent),
    feeder(feeder),
    ui(new Ui::FeederControl)
{
    ui->setupUi(this);
}

FeederControl::~FeederControl()
{
    delete ui;
}
