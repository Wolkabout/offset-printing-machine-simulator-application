#include "alarmalert.h"
#include "ui_alarmalert.h"

#include <QMessageBox>

AlarmAlert::AlarmAlert(QString message, Simulator& simulator, QWidget* component, QWidget *parent) :
    QWidget(parent),
    message(message),
    component(component),
    simulator(simulator),
    ui(new Ui::AlarmAlert)
{
    ui->setupUi(this);

    QMetaObject::invokeMethod(ui->message, "setText", Qt::QueuedConnection, Q_ARG(QString, message));
//    Again, this is only if you want your car to blow your wheels and brakes off
//    ui->message->setText(message);
}

AlarmAlert::~AlarmAlert()
{
    delete ui;
}

void AlarmAlert::on_ok_clicked()
{
    this->hide();
}

void AlarmAlert::on_goto_2_clicked()
{
    if (message.contains("Feeder")) {
        simulator.getFeederWidget()->show();
    } else if (message.contains("Cyan")) {
        simulator.getCyanWidget()->show();
    } else if (message.contains("Magenta")) {
        simulator.getMagentaWidget()->show();
    } else if (message.contains("Yellow")) {
        simulator.getYellowWidget()->show();
    } else if (message.contains("Black")) {
        simulator.getBlackWidget()->show();
    } else if (message.contains("Delivery")) {
        simulator.getDeliveyWidget()->show();
    } else {
        QMessageBox * messageBox = new QMessageBox(this);
        messageBox->setText("Could not find component causing the error!");
        messageBox->exec();
    }
    hide();
}
