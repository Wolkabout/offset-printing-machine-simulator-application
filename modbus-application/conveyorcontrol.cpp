#include "conveyorcontrol.h"
#include "ratelistener.h"
#include "ui_conveyorcontrol.h"

ConveyorControl::ConveyorControl(Conveyor& conveyor, QWidget *parent) :
    QWidget(parent),
    conveyor(conveyor),
    ui(new Ui::ConveyorControl)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::WindowStaysOnTopHint);
    ui->name->setText("<h2> " + QString::fromStdString(conveyor.getName()) + "</h2>");
    ui->rate->setText("<h2>" + QString::number(conveyor.getRatePerHour()) + "</h2>");

    listener = std::make_shared<RateListener>(conveyor, ui->rate);
    conveyor.getRateMessageReceivers().push_back(listener);
}

ConveyorControl::~ConveyorControl()
{
    delete ui;
}

void ConveyorControl::windowActivationChange(bool oldChange)
{
    if (oldChange) {
        hide();
    }
}

void ConveyorControl::on_decrease_clicked()
{
    if (conveyor.getRatePerHour() > conveyor.getMinRatePerHour()) {
        conveyor.setRatePerHour(conveyor.getRatePerHour() - 100);
    }
}

void ConveyorControl::on_increase_clicked()
{
    if (conveyor.getRatePerHour() < conveyor.getMaxRatePerHour()) {
        conveyor.setRatePerHour(conveyor.getRatePerHour() + 100);
    }
}

void ConveyorControl::on_failure_clicked()
{
    hide();
    conveyor.Emit(Severe, conveyor.getName() + " has stopped working!");
}

void ConveyorControl::on_ok_clicked()
{
    hide();
}
