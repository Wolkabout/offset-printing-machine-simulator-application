#include "conveyorcontrol.h"
#include "ui_conveyorcontrol.h"

ConveyorControl::ConveyorControl(Conveyor& conveyor, QWidget *parent) :
    QWidget(parent),
    conveyor(conveyor),
    ui(new Ui::ConveyorControl)
{
    ui->setupUi(this);
    ui->name->setText("<h2> " + QString::fromStdString(conveyor.getName()) + "</h2>");

    listener = std::make_shared<RateListener>(*this, conveyor, ui->rate);
    conveyor.getRateMessageReceivers().push_back(listener);

    ui->rate->setText("<h2>" + QString::number(conveyor.getRatePerHour()) + "</h2>");
}

ConveyorControl::RateListener::RateListener(ConveyorControl& cc, Conveyor& conveyor, QLabel * rateLabel)
    : cc(cc), conveyor(conveyor), rateLabel(rateLabel) { }

void ConveyorControl::RateListener::ReceiveMessage(std::shared_ptr<ConveyorRateMessage> message) {
    QMetaObject::invokeMethod(rateLabel, "setText", Qt::QueuedConnection, Q_ARG(QString, "<h2>" + QString::number(message->getCurrentRate()) + "</h2>"));
};

ConveyorControl::~ConveyorControl()
{
    delete ui;
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
