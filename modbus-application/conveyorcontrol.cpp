#include "conveyorcontrol.h"
#include "ui_conveyorcontrol.h"

ConveyorControl::ConveyorControl(Conveyor& conveyor, QWidget *parent) :
    QWidget(parent),
    conveyor(conveyor),
    ui(new Ui::ConveyorControl)
{
    ui->setupUi(this);
}

ConveyorControl::~ConveyorControl()
{
    delete ui;
}
